#include "downloader.hpp"
#include "download_progress.hpp"

#include <curl/curl.h>

#include <fstream>
#include <iostream>

namespace src
{

    namespace
    {
        size_t writeCallback(
            void *contents,
            size_t size,
            size_t nmemb,
            void *userp)
        {
            auto *str = static_cast<std::string *>(userp);

            size_t total = size * nmemb;

            str->append(
                static_cast<char *>(contents),
                total);

            return total;
        }

        size_t writeFileCallback(
            void *contents,
            size_t size,
            size_t nmemb,
            void *userp)
        {
            auto *file = static_cast<std::ofstream *>(userp);

            size_t total = size * nmemb;

            file->write(
                static_cast<char *>(contents),
                total);

            return total;
        }
    }

    bool Downloader::download(
        const std::string &url,
        std::string &data)
    {
        data.clear();
        lastError.clear();

        CURL *curl = curl_easy_init();

        if (!curl)
            return false;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "src/0.3.0");
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        CURLcode result = curl_easy_perform(curl);

        long response = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

        if (result != CURLE_OK)
        {
            lastError = curl_easy_strerror(result);
        }
        else if (response != 200)
        {
            lastError = "HTTP " + std::to_string(response);
        }
        else
        {
            lastError.clear();
        }

        curl_easy_cleanup(curl);

        return result == CURLE_OK && response == 200;
    }

    bool Downloader::downloadFile(
        const std::string &url,
        const std::filesystem::path &destination)
    {
        lastError.clear();
        DownloadProgress progress;

        std::ofstream file(
            destination,
            std::ios::binary);

        if (!file)
            return false;

        CURL *curl = curl_easy_init();

        if (!curl)
            return false;

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

        curl_easy_setopt(
            curl,
            CURLOPT_XFERINFOFUNCTION,
            DownloadProgress::progressCallback);

        curl_easy_setopt(
            curl,
            CURLOPT_XFERINFODATA,
            &progress);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "src/0.3.0");
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFileCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

        CURLcode result = curl_easy_perform(curl);

        long response = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

        bool success =
            result == CURLE_OK &&
            response == 200;

        if (success)
        {
            progress.finish();
        }

        if (result == CURLE_HTTP_RETURNED_ERROR)
        {
            lastError = "HTTP " + std::to_string(response);
        }
        else if (result != CURLE_OK)
        {
            lastError = curl_easy_strerror(result);
        }
        else if (response != 200)
        {
            lastError = "HTTP " + std::to_string(response);
        }
        else
        {
            lastError.clear();
        }

        curl_easy_cleanup(curl);
        file.close();

        return success;
    }
}