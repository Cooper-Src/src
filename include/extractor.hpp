#pragma once

#include <filesystem>

namespace src
{
    class Extractor
    {
    public:
        static bool extractZip(
            const std::filesystem::path& zipFile,
            const std::filesystem::path& destination);
    };
}