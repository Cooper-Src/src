#pragma once

#include <string>

namespace src
{
    struct SourceInfo
    {
        std::string type;
        std::string url;
        std::string format;
    };

    struct LicenseInfo
    {
        std::string name;
    };

    struct HomepageInfo
    {
        std::string url;
    };

    class PackageManifest
    {
    public:
        std::string name;
        std::string version;
        std::string description;

        SourceInfo source;
        LicenseInfo license;
        HomepageInfo homepage;

        bool valid() const;
    };
}