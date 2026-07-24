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

    std::filesystem::path Paths::packageDirectory()
    {
        auto path = localAppData() / "src" / "packages";

        std::filesystem::create_directories(path);

        return path;
    }
}