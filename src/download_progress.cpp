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

        std::string bar;

        for (int i = 0; i < width; ++i)
        {
            bar += "─";
        }

        if (total > 0)
        {
            int filled =
                static_cast<int>(percent * width / 100.0);

            for (int i = 0; i < filled; ++i)
            {
                bar.replace(i * 3, 3, "█");
            }
        }
        else
        {
            constexpr int blockWidth = 5;

            int start =
                static_cast<int>(animationFrame % width);

            for (int i = 0; i < blockWidth; ++i)
            {
                int pos = (start + i) % width;
                bar.replace(pos * 3, 3, "█");
            }

            animationFrame =
                static_cast<std::size_t>(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        now.time_since_epoch())
                        .count() /
                    80);
        }
        std::ostringstream line;

        double downloadedMB = toMB(static_cast<double>(downloaded));
        double totalMB = toMB(static_cast<double>(total));

        // Force the last frame to show identical values
        if (downloaded >= total && total > 0)
        {
            downloadedMB = totalMB;
        }

        lastDownloaded = downloaded;
        lastTotal = total;
        lastSpeed = speed;

        line << '[' << bar << "] ";

        if (total > 0)
        {
            line << std::setw(3)
                 << static_cast<int>(percent)
                 << "%  "
                 << std::fixed
                 << std::setprecision(1)
                 << downloadedMB
                 << " MB / "
                 << totalMB
                 << " MB";
        }
        else
        {
            line << std::fixed
                 << std::setprecision(1)
                 << downloadedMB
                 << " MB";
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
        animationFrame = 0;
        std::cout << '\n';
    }
}