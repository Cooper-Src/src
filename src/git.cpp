#include "git.hpp"
#include "paths.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace src
{
    bool src::Git::clone(const std::string &url)
    {
        auto destination = Paths::packageDirectory() / repositoryName(url);

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


std::string src::Git::repositoryName(const std::string& url)
{
    auto slash = url.find_last_of('/');

    std::string name = slash == std::string::npos
                           ? url
                           : url.substr(slash + 1);

    if (name.size() >= 4 &&
        name.substr(name.size() - 4) == ".git")
    {
        name.erase(name.size() - 4);
    }

    return name;
}

bool src::Git::isRepositoryUrl(const std::string &input)
{
    return input.rfind("http://", 0) == 0 ||
           input.rfind("https://", 0) == 0 ||
           input.rfind("git@", 0) == 0;
}