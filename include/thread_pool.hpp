#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace src
{
    class ThreadPool
    {
    public:
        explicit ThreadPool(std::size_t threadCount);

        ~ThreadPool();

        void enqueue(std::function<void()> task);

        void wait();

    private:
        void worker();

        std::vector<std::thread> m_workers;

        std::queue<std::function<void()>> m_tasks;

        std::mutex m_mutex;

        std::condition_variable m_condition;

        bool m_stop = false;

        std::size_t m_activeWorkers = 0;
    };
}