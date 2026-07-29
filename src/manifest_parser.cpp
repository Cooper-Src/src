#include "manifest_parser.hpp"
#include "string_utils.hpp"

#include <fstream>
#include <iostream>
#include <string>

namespace src
{
    bool ManifestParser::parse(const std::filesystem::path &path,
                               PackageManifest &manifest)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::cout << "Failed to open: " << path << '\n';
            return false;
        }

        std::string line;
        std::string currentSection;
        while (std::getline(file, line))
        {
            line = StringUtils::trim(line);

            if (line.empty())
            {
                continue;
            }

            if (StringUtils::startsWith(line, '#') ||
                StringUtils::startsWith(line, ';'))

            {
                continue;
            }
            if (StringUtils::startsWith(line, '[') &&
                line.back() == ']')
            {
                currentSection = line.substr(1, line.size() - 2);

                continue;
            }
            auto [key, value] = StringUtils::splitKeyValue(line);

            if (key.empty())
            {
                continue;
            }
            if (currentSection.empty())
            {
                if (key == "name")
                {
                    manifest.name = value;
                }
                else if (key == "version")
                {
                    manifest.version = value;
                }
                else if (key == "description")
                {
                    manifest.description = value;
                }
            }
            else if (currentSection == "source")
            {
                if (key == "type")
                {
                    manifest.source.type = value;
                }
                else if (key == "url")
                {
                    manifest.source.url = value;
                }
                else if (key == "branch")
                {
                    manifest.source.format = value;
                }
            }
            else if (currentSection == "license")
            {
                if (key == "name")
                {
                    manifest.license.name = value;
                }
            }
            else if (currentSection == "homepage")
            {
                if (key == "url")
                {
                    manifest.homepage.url = value;
                }
            }
        }

        return manifest.valid();
    }
}