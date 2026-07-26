#pragma once

#include <filesystem>

namespace src
{
    class Cleanup
    {
    public:
        static void removeGitFiles(
            const std::filesystem::path& root);
    };
}