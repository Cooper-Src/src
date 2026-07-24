#pragma once

#include "package_manifest.hpp"

#include <filesystem>

namespace src
{
    class ManifestParser
    {
    public:
        static bool parse(const std::filesystem::path& path,
                          PackageManifest& manifest);
    };
}