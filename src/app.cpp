#include "app.hpp"
#include "command.hpp"

#include <vector>
#include <string>

namespace src
{
    int App::run(int argc, char* argv[])
    {
        if (argc < 2)
        {
            Command command;
            return command.execute("help", {});
        }

        std::string commandName = argv[1];

        std::vector<std::string> arguments;

        for (int i = 2; i < argc; ++i)
            arguments.emplace_back(argv[i]);

        Command command;
        return command.execute(commandName, arguments);
    }
}