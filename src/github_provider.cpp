#include "github_provider.hpp"
#include "downloader.hpp"

#include <iostream>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace src
{
    bool GitHubProvider::supports(const std::string &url)
    {
        return url.find("github.com") != std::string::npos;
    }

    bool GitHubProvider::ownerRepo(
        const std::string &url,
        std::string &owner,
        std::string &repo)
    {
        const std::string prefix = "https://github.com/";

        if (url.rfind(prefix, 0) != 0)
        {
            return false;
        }

        std::string path = url.substr(prefix.size());

        std::size_t slash = path.find('/');

        if (slash == std::string::npos)
        {
            return false;
        }

        owner = path.substr(0, slash);

        repo = path.substr(slash + 1);

        if (repo.size() > 4 &&
            repo.substr(repo.size() - 4) == ".git")
        {
            repo.erase(repo.size() - 4);
        }

        return true;
    }
    std::string GitHubProvider::archiveUrl(
        const std::string &owner,
        const std::string &repo,
        const std::string &branch)
    {
        return "https://codeload.github.com/" +
               owner +
               "/" +
               repo +
               "/zip/refs/heads/" +
               branch;
    }

    bool GitHubProvider::defaultBranch(
        const std::string &owner,
        const std::string &repo,
        std::string &branch)
    {
        Downloader downloader;

        std::string data;

        std::string url =
            "https://api.github.com/repos/" +
            owner +
            "/" +
            repo;

        if (!downloader.download(url, data))
        {
            std::cout << "Download failed\n";
            return false;
        }

        json response = json::parse(data);

        if (!response.contains("default_branch"))
        {
            std::cout << "default_branch not found\n";
            return false;
        }

        branch = response["default_branch"].get<std::string>();

        return true;
    }
}