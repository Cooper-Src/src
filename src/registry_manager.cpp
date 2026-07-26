#include "registry_manager.hpp"
#include "downloader.hpp"
#include "paths.hpp"
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using json = nlohmann::json;

namespace src
{
    bool RegistryManager::update()
    {

        Downloader downloader;

        std::string index;

        std::cout << "Pulling registry index\n";

        if (!downloader.download(
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
        int updated = 0;
        int failed = 0;
        int current = 0;
        for (const auto &manifest : registry["manifests"])
        {
            manifests.push_back(manifest.get<std::string>());
        }
        int total = static_cast<int>(manifests.size());
        for (const auto &manifest : manifests)

        {
            ++current;

            std::cout << "\rUpdating manifests... ("
                      << current
                      << "/"
                      << total
                      << ")"
                      << std::flush;

            std::string data;

            std::string url =
                "https://cooper-src.github.io/src-registry/manifests/" +
                manifest;

            if (!downloader.download(url, data))
            {
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
        }
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
            << "Updated           : " << updated << '\n'
            << "Failed            : " << failed << '\n';

        return true;
    }

}