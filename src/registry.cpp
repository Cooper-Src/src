#include "registry.hpp"
#include "manifest_parser.hpp"
#include "paths.hpp"

#include <filesystem>
#include <algorithm>
#include <iostream>

namespace src
{
    bool Registry::load(const std::string &package,
                        PackageManifest &manifest)
    {
        std::filesystem::path path = Paths::registryDirectory();

        path /= package + ".src";

        return ManifestParser::parse(path, manifest);
    }
    int Registry::search(const std::string &query)
    {
        bool found = false;

        for (const auto &entry :
             std::filesystem::directory_iterator(Paths::registryDirectory()))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".src")
                continue;

            PackageManifest manifest;

            if (!ManifestParser::parse(entry.path(), manifest))
                continue;

            std::string name = manifest.name;
            std::string search = query;

            std::transform(name.begin(), name.end(),
                           name.begin(), ::tolower);

            std::transform(search.begin(), search.end(),
                           search.begin(), ::tolower);

            if (name.find(search) != std::string::npos)
            {
                std::cout << manifest.name << '\n';
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "No packages found.\n";
            return 1;
        }

        return 0;
    }
}
