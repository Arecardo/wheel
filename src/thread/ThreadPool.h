#ifndef __C_THREADPOOL_H__
#define __C_THREADPPOL_H__

#include "Task.h"
#include <thread>
#include <future>
#include <condition_variable>
#include <vector>
#include <queue>
#include <memory>

namespace wheel
{
class ThreadPool
{
public:
    explicit ThreadPool(size_t thread_num = std::thread::hardware_concurrency()): m_stop(false)
    {
        try{
            for (size_t i = 0; i < thread_num; i++)
            {
                m_threads.emplace_back([this]{
                    while (true)
                    {
                        std::unique_lock<std::mutex> lck(m_queueMtx);
                        m_cond.wait(lck, [this]{return m_stop || !m_tasks.empty();});
                        if (m_stop && m_tasks.empty())
                        {
                            return;
                        }
                        auto task = std::move(m_tasks.front());
                        m_tasks.pop();
                        task();
                    }
                });
            }
        }
        catch (...)
        {
            m_stop = true;
            throw;
        }
    }

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lck(m_queueMtx);
            if (m_stop)
            {
                throw std::runtime_error("Enqueue on stopped ThreadPool");
                m_tasks.emplace([task](){(*task)();});
            }
            m_cond.notify_one();
            return res;
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lck(m_queueMtx);
            m_stop = true;
        }
        m_cond.notify_all();
        for (std::thread &worker : m_threads)
        {
            worker.join();
        }
    }
private:
    std::vector<std::thread> m_threads;
    std::queue<Task> m_tasks;

    std::mutex m_queueMtx;
    std::condition_variable m_cond;
    bool m_stop = false;
};
} // namespace wheel

#endif // __C_THREADPPOL_H__
