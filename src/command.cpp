#include "command.hpp"
#include "git.hpp"
#include "paths.hpp"
#include "manifest_parser.hpp"
#include "package_manifest.hpp"
#include "string_utils.hpp"
#include "registry.hpp"
#include "package_manifest.hpp"

#include <filesystem>
#include <iostream>
#include <cstdlib>

namespace src
{
    int Command::execute(const std::string &command,
                         const std::vector<std::string> &arguments)
    {
        if (command == "manifest")
            return manifest(arguments);

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

    pull <package/git-url>       Install a package or clone a Git repository
    list                         List installed packages
    update <package>             Update an installed package
    remove <package>             Remove an installed package

Developer Commands:
    manifest <file>              Parse and display a .src manifest

Examples:
    src pull raylib
    src pull https://github.com/raysan5/raylib.git

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
        std::cout << "src v0.1.0\n";
        return 0;
    }

    int Command::pull(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Missing package name or repository URL.\n";
            return 1;
        }

        Git git;

        // Direct repository URL
        if (Git::isRepositoryUrl(arguments[0]))
        {
            std::string repoName = git.repositoryName(arguments[0]);

            auto packagePath =
                Paths::packageDirectory() / repoName;

            if (std::filesystem::exists(packagePath))
            {
                std::cout << "Package '" << repoName
                          << "' is already installed.\n";
                std::cout << "Run 'src update "
                          << repoName
                          << "' to update it.\n";

                return 1;
            }

            std::cout << "Failed to clone repository.\n";
            return 1;
        }

        // Registry package
        PackageManifest manifest;

        if (!Registry::load(arguments[0], manifest))
        {
            std::cout << "Package '" << arguments[0]
                      << "' was not found.\n";
            return 1;
        }

        if (git.clone(manifest.sourceUrl))
        {
            std::cout << "Package installed successfully.\n";
            return 0;
        }

        std::cout << "Failed to install package.\n";
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
                      << "' (" << removed << " items deleted).\n";

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
            std::cout << "Missing package name.\n";
            return 1;
        }

        const auto package = Paths::packageDirectory() / arguments[0];

        if (!std::filesystem::exists(package))
        {
            std::cout << "Package '" << arguments[0]
                      << "' is not installed.\n";
            return 1;
        }

        std::string command =
            "git -C \"" +
            package.string() +
            "\" pull";

        std::cout << "Updating '" << arguments[0] << "'...\n";

        int result = std::system(command.c_str());

        if (result == 0)
        {
            std::cout << "Package updated successfully.\n";
        }
        else
        {
            std::cout << "Failed to update package.\n";
        }

        return result;
    }

    int Command::manifest(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Usage: src manifest <file>\n";
            return 1;
        }

        PackageManifest manifest;

        if (!ManifestParser::parse(arguments[0], manifest))
        {
            std::cout << "Failed to parse manifest.\n";
            return 1;
        }

        std::cout << "\nPackage Manifest\n";
        std::cout << "================\n\n";

        std::cout << "Name:        " << manifest.name << '\n';
        std::cout << "Version:     " << manifest.version << '\n';
        std::cout << "Description: " << manifest.description << "\n\n";

        std::cout << "Source\n";
        std::cout << "------\n";
        std::cout << "Type:        " << manifest.sourceType << '\n';
        std::cout << "URL:         " << manifest.sourceUrl << '\n';
        std::cout << "Branch:      " << manifest.sourceBranch << "\n\n";

        std::cout << "License:     " << manifest.license << '\n';
        std::cout << "Homepage:    " << manifest.homepage << '\n';

        return 0;
    }
}