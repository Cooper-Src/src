#include "cleanup.hpp"

#include <iostream>

namespace src
{
    void Cleanup::removeGitFiles(
        const std::filesystem::path& root)
    {
        if (!std::filesystem::exists(root))
        {
            return;
        }

        for (auto it =
                 std::filesystem::recursive_directory_iterator(root);
             it != std::filesystem::recursive_directory_iterator();)
        {
            const auto path = it->path();
            const std::string name =
                path.filename().string();

            if (name.rfind(".git", 0) == 0)
            {
                std::error_code error;

                if (it->is_directory())
                {
                    it.disable_recursion_pending();
                }

                std::filesystem::remove_all(path, error);

                if (error)
                {
                    std::cout
                        << "Failed to remove "
                        << path.filename().string()
                        << '\n';
                }

                it.increment(error);
            }
            else
            {
                ++it;
            }
        }
    }
}