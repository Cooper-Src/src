#include "command.hpp"
#include "paths.hpp"
#include "manifest_parser.hpp"
#include "package_manifest.hpp"
#include "string_utils.hpp"
#include "registry.hpp"
#include "package_manifest.hpp"
#include "registry_manager.hpp"
#include "package_downloader.hpp"

#include <filesystem>
#include <iostream>
#include <cstdlib>

namespace src
{

    int Command::execute(const std::string &command,
                         const std::vector<std::string> &arguments)
    {
        if (command == "help")
            return help();

        if (command == "version")
            return version();

        if (command == "pull")
            return pull(arguments);

        if (command == "list")
            return list();

        if (command == "remove")
            return remove(arguments);

        if (command == "update")
            return update(arguments);

        if (command == "search")
            return search(arguments);

        if (command == "registry")
            return registry(arguments);

        if (command == "info")
        {
            return Command::info(arguments);
        }

        std::cout << "Unknown command: " << command << '\n';
        return 1;
    }

    int Command::help()
    {
        std::cout <<
            R"(src v0.2.0
A lightweight source retrieval tool.

Usage:
    src <command> [arguments]

Commands:
    help                         Show this help message
    version                      Show the current version

    pull <package/>       Install a package
    list                         List installed packages
    update <package>             Update an installed package
    remove <package>             Remove an installed package

Developer Commands:
    manifest <file>              Parse and display a .src manifest

Examples:
    src pull raylib
    src list
    src update raylib
    src remove raylib

Packages are stored in:
    %LOCALAPPDATA%\src\packages
)";

        return 0;
    }
    int Command::version()
    {
        std::cout << "src v0.3.0\n";
        return 0;
    }

    int Command::pull(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Missing package name.\n";
            return 1;
        }

        PackageDownloader downloader;

        // Registry package
        PackageManifest manifest;

        if (!Registry::load(arguments[0], manifest))
        {
            std::cout << "Package '" << arguments[0]
                      << "' was not found.\n";
            return 1;
        }

        auto packagePath =
            Paths::packageDirectory() / manifest.name;

        if (std::filesystem::exists(packagePath))
        {
            std::cout << "Package '" << manifest.name
                      << "' is already installed.\n";
            return 1;
        }

        if (downloader.install(manifest))
        {
            return 0;
        }

        
        return 1;
    }

    int Command::list()
    {
        auto packageDir = Paths::packageDirectory();

        bool found = false;

        std::cout << "Installed packages\n\n";

        for (const auto &entry : std::filesystem::directory_iterator(packageDir))
        {
            if (!entry.is_directory())
                continue;

            std::cout << entry.path().filename().string() << '\n';
            found = true;
        }

        if (!found)
        {
            std::cout << "No packages installed.\n";
        }

        return 0;
    }

    int Command::remove(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Missing package name.\n";
            return 1;
        }

        if (arguments[0] == "." || arguments[0] == ".." || arguments[0].empty())
        {
            std::cout << "Invalid package name.\n";
            return 1;
        }

        const auto package = Paths::packageDirectory() / arguments[0];

        if (!std::filesystem::exists(package))
        {
            std::cout << "Package '" << arguments[0]
                      << "' is not installed.\n";
            return 1;
        }

        try
        {
            std::uintmax_t removed = std::filesystem::remove_all(package);

            std::cout << "Removed '" << arguments[0]
                      << "' (" << removed << " items deleted).";

            return 0;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cout << "Failed to remove package.\n";
            std::cout << e.what() << '\n';

            return 1;
        }
    }

    int Command::update(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Updating all installed packages...\n\n";

            int updated = 0;
            int failed = 0;

            for (const auto &entry :
                 std::filesystem::directory_iterator(Paths::packageDirectory()))
            {
                if (!entry.is_directory())
                    continue;

                if (updatePackage(entry.path().filename().string()) == 0)
                    ++updated;
                else
                    ++failed;
            }

            std::cout << "\nSummary\n";
            std::cout << "-------\n";
            std::cout << "Updated : " << updated << '\n';
            std::cout << "Failed  : " << failed << '\n';

            return failed == 0 ? 0 : 1;
        }

        return updatePackage(arguments[0]);
    }

    int Command::updatePackage(const std::string &packageName)
    {
        std::cout << "Updating '" << packageName << "'...\n";

        auto package =
            Paths::packageDirectory() / packageName;

        if (std::filesystem::exists(package))
        {
            std::filesystem::remove_all(package);
        }

        return pull({packageName});
    }

    int Command::registry(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Usage: src registry <command>\n";
            return 1;
        }
        if (arguments[0] == "update")
        {
            RegistryManager manager;

            return manager.update() ? 0 : 1;
        }

        std::cout << "Unknown registry command.\n";
        return 1;
    }
    int Command::search(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Missing search query.\n";
            return 1;
        }

        return Registry::search(arguments[0]);
    }
    int Command::info(const std::vector<std::string> &arguments)
    {

        if (arguments.empty())
        {
            std::cout << "Missing package name.\n";
            return 1;
        }

        auto manifestPath =
            Paths::registryDirectory() /
            (arguments[0] + ".src");

        bool installed =
            std::filesystem::exists(
                Paths::packageDirectory() / arguments[0]);

        if (!std::filesystem::exists(manifestPath))
        {
            std::cout << "Package not found.\n";
            return 1;
        }
        PackageManifest manifest;
        ManifestParser parser;

        if (!parser.parse(manifestPath, manifest))
        {
            std::cout << "Failed to parse manifest.\n";
            return 1;
        }
        std::cout << "Package:     " << manifest.name << '\n';
        std::cout << "Version:     " << manifest.version << '\n';
        std::cout << "Description: " << manifest.description << '\n';
        std::cout << "License:     " << manifest.license.name << '\n';
        std::cout << "Homepage:    " << manifest.homepage.url << '\n';
        std::cout << "Source:      " << manifest.source.url << '\n';
        std::cout << '\n';

        if (installed)
        {
            std::cout << "Installed:   Yes\n";
            std::cout << "Location:    "
                      << (Paths::packageDirectory() / manifest.name).string()
                      << '\n';
        }
        else
        {
            std::cout << "Installed:   No\n";
        }

        return 0;
    }
}