#include "extractor.hpp"
#include "miniz.h"
#include "download_progress.hpp"
#include "task_progress.hpp"

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace
{
    std::string stripTopDirectory(const std::string &path)
    {
        auto pos = path.find('/');

        if (pos == std::string::npos)
            return {};

        return path.substr(pos + 1);
    }
}

namespace src
{
    bool Extractor::extractZip(
        const fs::path &zipFile,
        const fs::path &destination)
    {
        mz_zip_archive zip{};
        memset(&zip, 0, sizeof(zip));

        if (!mz_zip_reader_init_file(
                &zip,
                zipFile.string().c_str(),
                0))
        {
            std::cout << "Failed to open zip archive.\n";
            return false;
        }

        fs::create_directories(destination);

        // ProgressBar progress;

        mz_uint fileCount =
            mz_zip_reader_get_num_files(&zip);

        TaskProgress progress;
        progress.update(
            0,
            fileCount,
            "");
        for (mz_uint i = 0; i < fileCount; ++i)
        {
            mz_zip_archive_file_stat fileInfo{};

            if (!mz_zip_reader_file_stat(
                    &zip,
                    i,
                    &fileInfo))
            {
                mz_zip_reader_end(&zip);
                return false;
            }

            std::string relative =
                stripTopDirectory(fileInfo.m_filename);

            // Skip the GitHub root folder itself.
            if (relative.empty())
                continue;

            fs::path output =
                destination / relative;

            if (mz_zip_reader_is_file_a_directory(&zip, i))
            {
                fs::create_directories(output);
            }
            else
            {
                fs::create_directories(
                    output.parent_path());

                if (!mz_zip_reader_extract_to_file(
                        &zip,
                        i,
                        output.string().c_str(),
                        0))
                {
                    std::cout
                        << "Failed to extract "
                        << relative
                        << '\n';

                    mz_zip_reader_end(&zip);
                    return false;
                }
                progress.update(
                    i + 1,
                    fileCount,
                    relative);
            }

            // progress.update(
            // i + 1,
            // fileCount,
            // 0.0);
        }

        progress.finish();

        mz_zip_reader_end(&zip);

        return true;
    }
}