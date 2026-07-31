#include "thread_pool.hpp"

namespace src
{

ThreadPool::ThreadPool(std::size_t threadCount)
{
    for (std::size_t i = 0; i < threadCount; i++)
    {
        m_workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard lock(m_mutex);
        m_stop = true;
    }

    m_condition.notify_all();

    for (auto& worker : m_workers)
        worker.join();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard lock(m_mutex);
        m_tasks.push(std::move(task));
    }

    m_condition.notify_one();
}

void ThreadPool::worker()
{
    while (true)
    {
        std::function<void()> task;

        {
            std::unique_lock lock(m_mutex);

            m_condition.wait(lock,
                [&]
                {
                    return m_stop || !m_tasks.empty();
                });

            if (m_stop && m_tasks.empty())
                return;

            task = std::move(m_tasks.front());
            m_tasks.pop();

            ++m_activeWorkers;
        }

        task();

        {
            std::lock_guard lock(m_mutex);

            --m_activeWorkers;

            if (m_tasks.empty() && m_activeWorkers == 0)
                m_condition.notify_all();
        }
    }
}

void ThreadPool::wait()
{
    std::unique_lock lock(m_mutex);

    m_condition.wait(lock,
        [&]
        {
            return m_tasks.empty() && m_activeWorkers == 0;
        });
}

}