#include "downloader.hpp"
#include "download_progress.hpp"

#include <curl/curl.h>

#include <cstdio>
#include <iostream>
#include <chrono>
#include <cmath>

namespace
{
    size_t writeCallback(
        void *contents,
        size_t size,
        size_t nmemb,
        void *userp)
    {
        auto *data = static_cast<std::string *>(userp);

        data->append(
            static_cast<char *>(contents),
            size * nmemb);

        return size * nmemb;
    }

    size_t writeFileCallback(
        void *contents,
        size_t size,
        size_t nmemb,
        void *userp)
    {
        FILE *file = static_cast<FILE *>(userp);

        size_t written =
            fwrite(contents, size, nmemb, file);

        return written * size;
    }
    struct DownloadContext
    {
        double speed = 0.0;
        src::DownloadProgress bar;

        std::chrono::steady_clock::time_point start =
            std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point lastUpdate =
            start;

        std::uint64_t lastBytes = 0;
        std::uint64_t totalBytes = 0;
        double lastSpeed = 0.0;
    };
    static int progressCallback(
        void *clientp,
        curl_off_t dltotal,
        curl_off_t dlnow,
        curl_off_t,
        curl_off_t)
    {
        auto *progress =
            static_cast<DownloadContext *>(clientp);

        std::uint64_t downloaded =
            dlnow > 0
                ? static_cast<std::uint64_t>(dlnow)
                : 0;

        std::uint64_t total =
            dltotal > 0
                ? static_cast<std::uint64_t>(dltotal)
                : 0;

        auto elapsed =
            std::chrono::duration<double>(
                std::chrono::steady_clock::now() -
                progress->start)
                .count();

        double speed = 0.0;

        if (elapsed > 0.0)
        {
            speed =
                static_cast<double>(downloaded) / elapsed;
        }

        progress->totalBytes = total;
        progress->lastSpeed = speed;

        progress->bar.update(
            downloaded,
            total,
            speed);

        return 0;
    }
}

namespace src
{
    bool Downloader::download(
        const std::string &url,
        std::string &data)
    {
        data.clear();

        CURL *curl = curl_easy_init();

        if (!curl)
            return false;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "src/0.1");

        // Response callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        CURLcode result = curl_easy_perform(curl);

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

        curl_easy_cleanup(curl);

        if (result != CURLE_OK)
        {

            return false;
        }

        return true;
    }

    bool Downloader::downloadFile(
        const std::string &url,
        const std::filesystem::path &destination)
    {
        FILE *file = nullptr;

#ifdef _WIN32
        fopen_s(&file, destination.string().c_str(), "wb");
#else
        file = fopen(destination.string().c_str(), "wb");
#endif

        if (!file)
            return false;

        CURL *curl = curl_easy_init();

        if (!curl)
        {
            fclose(file);
            return false;
        }
        DownloadContext progress;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFileCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressCallback);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progress);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 1024L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "src/0.1");
        curl_easy_setopt(curl,
                         CURLOPT_WRITEFUNCTION,
                         writeFileCallback);

        curl_easy_setopt(curl,
                         CURLOPT_WRITEDATA,
                         file);

        CURLcode result = curl_easy_perform(curl);
        long status = 0;

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

        curl_easy_cleanup(curl);
        fclose(file);

        progress.bar.finish();

        if (result != CURLE_OK)
        {
            return false;
        }

        if (status != 200)
        {
            return false;
        }

        return true;
    }
}