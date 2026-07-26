#pragma once

#include <string>
#include <filesystem>

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
    };
}