#pragma once

#include <cstdint>
#include <chrono>

namespace src
{
    class DownloadProgress
    {
    public:
        DownloadProgress();

        void update(
            std::uint64_t downloaded,
            std::uint64_t total,
            double speed);

        void finish();

    private:
        bool started = false;

        std::uint64_t lastBytes = 0;

        std::chrono::steady_clock::time_point lastTime;
        std::chrono::steady_clock::time_point lastFrame;
        std::uint64_t lastDownloaded = 0;
        std::uint64_t lastTotal = 0;
        double lastSpeed = 0.0;
    };
}