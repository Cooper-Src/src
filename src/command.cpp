#include "command.hpp"
#include "git.hpp"

#include <iostream>

namespace src
{
    int Command::execute(const std::string& command,
                         const std::vector<std::string>& arguments)
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
            return update();

        std::cout << "Unknown command: " << command << '\n';
        return 1;
    }

    int Command::help()
    {
        std::cout << "Help\n";
        return 0;
    }

    int Command::version()
    {
        std::cout << "src v0.1.0\n";
        return 0;
    }

int Command::pull(const std::vector<std::string>& arguments)
{
    if (arguments.empty())
    {
        std::cout << "Missing repository URL.\n";
        return 1;
    }

    Git git;

    if (git.clone(arguments[0]))
    {
        std::cout << "Repository cloned successfully.\n";
        return 0;
    }

    std::cout << "Failed to clone repository.\n";
    return 1;
}

    int Command::list()
    {
        std::cout << "List\n";
        return 0;
    }

    int Command::remove(const std::vector<std::string>& arguments)
    {
        if (!arguments.empty())
            std::cout << "Remove: " << arguments[0] << '\n';
        else
            std::cout << "Missing package name.\n";

        return 0;
    }

    int Command::update()
    {
        std::cout << "Update\n";
        return 0;
    }
}