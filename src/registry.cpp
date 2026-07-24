#include "registry.hpp"
#include "manifest_parser.hpp"

#include <filesystem>

namespace src
{
    bool Registry::load(const std::string& package,
                        PackageManifest& manifest)
    {
        std::filesystem::path path = "../../registry";

        path /= package + ".src";

        return ManifestParser::parse(path, manifest);
    }
}