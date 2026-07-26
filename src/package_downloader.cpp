#include "package_downloader.hpp"
#include "github_provider.hpp"
#include "paths.hpp"
#include "downloader.hpp"
#include "extractor.hpp"

#include <iostream>

namespace src
{
    bool PackageDownloader::install(const PackageManifest &manifest)
    {

        GitHubProvider github;

        std::string owner;
        std::string repo;
        std::string branch;

        if (!github.ownerRepo(
                manifest.sourceUrl,
                owner,
                repo))
        {
            std::cout << "Invalid GitHub URL\n";
            return false;
        }

        if (!github.defaultBranch(owner, repo, branch))
        {
            std::cout << "Failed to determine default branch.\n";
            return false;
        }

        auto archive = Paths::temporaryFile(manifest.name);
        Downloader downloader;

        std::string archiveUrl =
            github.archiveUrl(owner, repo, branch);

        std::cout << "Downloading " << manifest.name << "...\n\n";

        if (!downloader.downloadFile(archiveUrl, archive))
        {
            std::cout << "Failed to download archive.\n";
            return false;
        }

        char* localAppData = nullptr;
size_t len = 0;

_dupenv_s(&localAppData, &len, "LOCALAPPDATA");

std::filesystem::path packages =
    std::filesystem::path(localAppData) /
    "src" /
    "packages";

free(localAppData);

        std::filesystem::path installPath =
            packages / manifest.name;

        std::filesystem::create_directories(installPath);

        if (!src::Extractor::extractZip(archive, installPath))
        {
            std::cout << "Failed to extract package.\n";
            return false;
        }

        std::filesystem::remove(archive);

        return true;
    }
}