#pragma once

#include <queue>
#include <mutex>

namespace src
{
    template<typename T>
    class ConcurrentQueue
    {
    public:
        void push(const T& item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(item);
        }

        bool pop(T& item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_queue.empty())
                return false;

            item = std::move(m_queue.front());
            m_queue.pop();

            return true;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.empty();
        }

    private:
        mutable std::mutex m_mutex;
        std::queue<T> m_queue;
    };
}