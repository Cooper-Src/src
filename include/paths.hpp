#pragma once

#include <filesystem>

namespace src
{
    class Paths
    {
    public:
        static std::filesystem::path localAppData();
        static std::filesystem::path packageDirectory();
    };
}