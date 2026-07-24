#pragma once

#include <string>

namespace src
{
    class PackageManifest
    {
    public:
        std::string name;
        std::string version;
        std::string description;

        std::string sourceType;
        std::string sourceUrl;
        std::string sourceBranch;

        std::string license;

        std::string homepage;
        bool valid() const;
    };
}