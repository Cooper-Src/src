#include "task_progress.hpp"

#include <chrono>
#include <iostream>

namespace src
{
    TaskProgress::TaskProgress()
    {
        lastFrame = std::chrono::steady_clock::now();
    }

    void TaskProgress::update(
        std::uint64_t current,
        std::uint64_t total,
        const std::string &filename)
    {
        if (!reserved)
        {
            std::cout << '\n';
            reserved = true;
        }
        else
        {
            // Move up to the first reserved line
            std::cout << "\x1b[2F";
        }

        std::cout
            << "Extracting ("
            << std::setw(4)
            << current
            << '/'
            << total
            << ")\x1b[K\n";

        std::cout
    << filename
    << "\x1b[K\n"
    << std::flush;
    }

    void TaskProgress::finish()
    {
        if (!started)
            return;
    }
}