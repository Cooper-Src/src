#pragma once

#include "package_manifest.hpp"


namespace src
{
    class PackageDownloader
    {
    public:
        bool install(const PackageManifest& manifest);
    };


}
