#include "string_utils.hpp"

#include <algorithm>
#include <cctype>

namespace src
{
    std::string StringUtils::trim(const std::string& text)
    {
        auto begin = std::find_if_not(
            text.begin(),
            text.end(),
            [](unsigned char c)
            {
                return std::isspace(c);
            });

        auto end = std::find_if_not(
            text.rbegin(),
            text.rend(),
            [](unsigned char c)
            {
                return std::isspace(c);
            }).base();

        if (begin >= end)
        {
            return "";
        }

        return std::string(begin, end);
    }

    bool StringUtils::startsWith(const std::string& text,
                                 char character)
    {
        return !text.empty() && text.front() == character;
    }

    std::pair<std::string, std::string>
    StringUtils::splitKeyValue(const std::string& line)
    {
        auto pos = line.find('=');

        if (pos == std::string::npos)
        {
            return {"", ""};
        }

        return
        {
            trim(line.substr(0, pos)),
            trim(line.substr(pos + 1))
        };
    }
}