#pragma once

#include <filesystem>

namespace src
{
    class Paths
{
public:
    static std::filesystem::path localAppData();

    static std::filesystem::path rootDirectory();
    static std::filesystem::path registryDirectory();
    static std::filesystem::path packageDirectory();

    static void initialize();
    static std::filesystem::path temporaryFile(
    const std::string& name);
};
}