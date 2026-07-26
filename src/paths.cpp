#include "paths.hpp"

#include <filesystem>

#include <windows.h>
#include <shlobj.h>

namespace src
{
    std::filesystem::path Paths::localAppData()
    {
        PWSTR path = nullptr;

        if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path)))
        {
            return {};
        }

        std::filesystem::path result(path);

        CoTaskMemFree(path);

        return result;
    }


std::filesystem::path Paths::rootDirectory()
{
    PWSTR path = nullptr;

    if (FAILED(SHGetKnownFolderPath(
            FOLDERID_LocalAppData,
            0,
            nullptr,
            &path)))
    {
        return {};
    }

    std::filesystem::path root(path);

    CoTaskMemFree(path);

    root /= "src";

    std::filesystem::create_directories(root);

    return root;
}

std::filesystem::path Paths::registryDirectory()
{
    auto path = rootDirectory() / "registry";

    std::filesystem::create_directories(path);

    return path;
}
std::filesystem::path Paths::packageDirectory()
{
    auto path = rootDirectory() / "packages";

    std::filesystem::create_directories(path);

    return path;
}
void Paths::initialize()
    {
        rootDirectory();
        registryDirectory();
        packageDirectory();
    }
    std::filesystem::path Paths::temporaryFile(
    const std::string& name)
{
    return std::filesystem::temp_directory_path() /
           ("src-" + name + ".zip");
}
}
