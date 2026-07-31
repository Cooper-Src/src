#pragma once

#include <cstdint>
#include <chrono>

#include <curl/curl.h>

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
        static int progressCallback(
            void *clientp,
            curl_off_t dltotal,
            curl_off_t dlnow,
            curl_off_t ultotal,
            curl_off_t ulnow);
        std::size_t animationFrame = 0;

    private:
        bool started = false;
        bool hasDrawn = false;
        bool completed = false;
        bool hasReceivedData = false;

        std::uint64_t lastBytes = 0;

        std::chrono::steady_clock::time_point lastTime;
        std::chrono::steady_clock::time_point lastFrame;
        std::uint64_t lastDownloaded = 0;
        std::uint64_t lastTotal = 0;
        double lastSpeed = 0.0;
    };
}