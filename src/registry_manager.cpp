#include "registry_manager.hpp"
#include "downloader.hpp"
#include "paths.hpp"
#include "thread_pool.hpp"
#include "concurrent_queue.hpp"

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <thread>

using json = nlohmann::json;

namespace src
{
    bool RegistryManager::update()
    {
        Downloader indexDownloader;

        std::string index;

        std::cout << "Pulling registry index\n";

        if (!indexDownloader.download(
                "https://cooper-src.github.io/src-registry/index.json",
                index))
        {
            std::cout << "Failed to download registry index.\n";
            return false;
        }

        json registry = json::parse(index);

        std::cout << "Registry version: "
                  << registry["version"] << "\n\n";

        std::vector<std::string> manifests;
        std::atomic<int> updated = 0;
        std::atomic<int> failed = 0;
        std::atomic<int> current = 0;
        for (const auto &manifest : registry["manifests"])
        {
            manifests.push_back(manifest.get<std::string>());
        }
        int total = static_cast<int>(manifests.size());

        ConcurrentQueue<std::string> queue;
        std::mutex consoleMutex;

        for (const auto &manifest : manifests)
        {
            queue.push(manifest);
        }
        const unsigned workers = 1024;

        ThreadPool pool(workers);
        for (unsigned i = 0; i < workers; i++)
        {
            pool.enqueue([&queue,
                          &current,
                          &updated,
                          &failed,
                          &consoleMutex,
                          total]()
                         {
        Downloader downloader;

        std::string manifest;

        while (queue.pop(manifest))
        {
            int progress = ++current;

            {
                std::lock_guard<std::mutex> lock(consoleMutex);

                std::cout
                    << "\rUpdating manifests... ("
                    << progress
                    << "/"
                    << total
                    << ")"
                    << std::flush;
            }

            std::string data;

            std::string url =
                "https://cooper-src.github.io/src-registry/manifests/" +
                manifest;

            if (!downloader.download(url, data))
{
    {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout
            << "\nFAILED: "
            << url
            << '\n';
    }

    ++failed;
    continue;
}

            std::filesystem::path path =
                Paths::registryDirectory() / manifest;

            std::ofstream file(path);

            if (!file)
            {
                ++failed;
                continue;
            }

            file << data;

            ++updated;
        } });
        }

        pool.wait();

        std::cout << '\n';

        std::cout << '\n';

        if (failed == 0)
        {
            std::cout << "Registry synchronized successfully.\n\n";
        }
        else
        {
            std::cout << "Registry synchronized with errors.\n\n";
        }

        std::cout
            << "Manifests checked : " << total << '\n'
            << "Updated           : " << updated.load() << '\n'
            << "Failed            : " << failed.load() << '\n';
        return true;
    }
}