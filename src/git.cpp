#include "git.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <windows.h>
#include <shlobj.h>

namespace src
{
    bool src::Git::clone(const std::string& url)
{
    auto destination = packageDirectory() / repositoryName(url);

    std::string command =
        "git clone \"" +
        url +
        "\" \"" +
        destination.string() +
        "\"";

    std::cout << command << '\n';

    return std::system(command.c_str()) == 0;
}
}

std::filesystem::path src::Git::packageDirectory() const
{
    PWSTR path = nullptr;

    if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path)))
    {
        return {};
    }

    std::filesystem::path packagePath(path);

    CoTaskMemFree(path);

    packagePath /= "src";
    packagePath /= "packages";

    std::filesystem::create_directories(packagePath);

    return packagePath;
}

std::string src::Git::repositoryName(const std::string& url) const
{
    auto slash = url.find_last_of('/');

    std::string name = slash == std::string::npos
        ? url
        : url.substr(slash + 1);

    if (name.ends_with(".git"))
    {
        name.erase(name.size() - 4);
    }

    return name;
}