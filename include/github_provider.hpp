#pragma once

#include <string>

namespace src
{
    class GitHubProvider
    {
    public:
        bool supports(const std::string& url);

        bool ownerRepo(
            const std::string& url,
            std::string& owner,
            std::string& repo);

        bool defaultBranch(
            const std::string& owner,
            const std::string& repo,
            std::string& branch);

        std::string archiveUrl(
            const std::string& owner,
            const std::string& repo,
            const std::string& branch);
    };
}