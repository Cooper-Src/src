#include "download_progress.hpp"

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace src
{

    double toMB(double bytes)
    {
        return bytes / 1024.0 / 1024.0;
    }

    DownloadProgress::DownloadProgress()
    {
        auto now = std::chrono::steady_clock::now();

        lastTime = now;
        lastFrame = now;
    }

    void DownloadProgress::update(
        std::uint64_t downloaded,
        std::uint64_t total,
        double speed)
    {
        double percent = 0.0;

        if (total > 0)
        {
            percent =
                std::round(downloaded * 100.0 / total);
        }
        else
        {
            percent = 0.0;
        }

        auto now = std::chrono::steady_clock::now();

        // Limit redraws to ~30 FPS
        if (started &&
            downloaded != total &&
            now - lastFrame < std::chrono::milliseconds(33))
        {
            return;
        }

        lastFrame = now;

        double elapsed =
            std::chrono::duration<double>(
                now - lastTime)
                .count();

        if (speed <= 0.0 && elapsed > 0.0)
        {
            speed =
                static_cast<double>(downloaded - lastBytes) /
                elapsed;
        }

        lastBytes = downloaded;
        lastTime = now;

        started = true;

        constexpr int width = 40;

        int filled =
            static_cast<int>(percent * width / 100.0);

        std::string bar;

        for (int i = 0; i < width; ++i)
        {
            bar += (i < filled) ? "█" : "─";
        }

        std::ostringstream line;

        double downloadedMB = toMB(static_cast<double>(downloaded));
        double totalMB = toMB(static_cast<double>(total));
        bool totalKnown = total > 0;

        // Force the last frame to show identical values
        if (downloaded >= total && total > 0)
        {
            downloadedMB = totalMB;
        }

        lastDownloaded = downloaded;
        lastTotal = total;
        lastSpeed = speed;

        line << '[' << bar << "] "
             << std::setw(3)
             << static_cast<int>(percent)
             << "%  "
             << std::fixed
             << std::setprecision(1)
             << downloadedMB
             << " MB / ";

        if (total > 0)
        {
            line << totalMB << " MB";
        }
        else
        {
            line << "Unknown";
        }

        line << "  "
             << toMB(speed)
             << " MB/s";

        std::cout << '\r'
                  << line.str()
                  << "\x1b[K"
                  << std::flush;
    }

    void DownloadProgress::finish()
    {
        update(lastDownloaded, lastTotal, lastSpeed);
        std::cout << '\n';
    }
}