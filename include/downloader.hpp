#pragma once

#include <filesystem>
#include <string>

namespace src
{
    class Downloader
    {
    public:
        bool download(
            const std::string &url,
            std::string &data);

        bool downloadFile(
            const std::string &url,
            const std::filesystem::path &destination);

         const std::string& getLastError() const
    {
        return lastError;
    }

    private:
        std::string lastError;
    };
}