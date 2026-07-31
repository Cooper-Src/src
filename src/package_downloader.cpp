#include "package_downloader.hpp"
#include "paths.hpp"
#include "downloader.hpp"
#include "extractor.hpp"
#include "cleanup.hpp"

#include <iostream>

namespace src
{
    bool PackageDownloader::install(const PackageManifest &manifest)
    {

        auto archive = Paths::temporaryFile(manifest.name);

        Downloader downloader;
        std::cout << "Downloading "
                  << manifest.name
                  << "...\n\n";

            if (!downloader.downloadFile(
                    manifest.source.url,
                    archive))
            {
                std::cout
                    << "Failed to download archive.\n"
                    << "Reason: "
                    << downloader.getLastError();

                return false;
            }

        std::filesystem::path installPath =
            src::Paths::packageDirectory() /
            manifest.name;

        std::filesystem::create_directories(installPath);

        if (!src::Extractor::extractZip(
                archive,
                installPath))
        {
            std::filesystem::remove(archive);
            std::cout << "Failed to extract package.\n";
            return false;
        }

        Cleanup::removeGitFiles(installPath);

        std::filesystem::remove(archive);

        std::cout
            << "\nSuccessfully installed " << manifest.name;

        if (!manifest.version.empty())
        {
            std::cout << ' ' << manifest.version;
        }

        std::cout
            << "\nLocation: " << installPath.string()
            << '\n';

        return true;
    }
}