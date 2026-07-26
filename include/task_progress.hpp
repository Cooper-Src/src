#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace src
{
    class TaskProgress
    {
    public:
        TaskProgress();

        void update(
            std::uint64_t current,
            std::uint64_t total,
            const std::string& filename);

        void finish();

    private:
        bool started = false;
          bool reserved = false;

        std::chrono::steady_clock::time_point lastFrame;
    };
}