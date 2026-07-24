#pragma once

#include <filesystem>
#include <string>

namespace src
{
    class Git
    {
    public:
        bool clone(const std::string& url);

    private:
        std::filesystem::path packageDirectory() const;
        std::string repositoryName(const std::string& url) const;
    };
}