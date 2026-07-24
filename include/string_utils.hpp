#pragma once

#include <string>
#include <utility>

namespace src
{
    class StringUtils
    {
    public:
        static std::string trim(const std::string& text);

        static bool startsWith(const std::string& text,
                               char character);

        static std::pair<std::string, std::string>
        splitKeyValue(const std::string& line);
    };
}