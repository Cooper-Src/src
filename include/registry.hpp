#pragma once

#include "package_manifest.hpp"

#include <string>

namespace src
{
    class Registry
    {
    public:
        static bool load(const std::string& package,
                         PackageManifest& manifest);
    };
}