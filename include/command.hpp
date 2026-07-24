#pragma once

#include <string>
#include <vector>

namespace src
{
    class Command
{
public:
    int execute(const std::string& command,
                const std::vector<std::string>& arguments);

private:
    int help();
    int version();
    int pull(const std::vector<std::string>& arguments);
    int list();
    int remove(const std::vector<std::string>& arguments);
    int update(const std::vector<std::string>& arguments);

    int manifest(const std::vector<std::string>& arguments);
};
}