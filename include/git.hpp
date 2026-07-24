#pragma once

#include <filesystem>
#include <string>

namespace src
{
    class Git
{
public:
    bool clone(const std::string& url);

    static bool isRepositoryUrl(const std::string& input);
    static std::string repositoryName(const std::string& url);
};
}