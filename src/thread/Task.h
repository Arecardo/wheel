#ifndef __C_TASK_H__
#define __C_TASK_H__

#include <functional>

namespace wheel
{
class Task
{
public:
    template<typename F, typename... Args>
    Task(F&& f, Args&& ...args)
    {
        task_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    // only allow move ctor
    Task(Task&& t) : task_(std::move(t.task_)) {}
    Task(const Task&) = delete;
    Task& operator=(Task&&) = delete;
    Task& operator=(const Task&) = delete;

    void operator()() {task_();}
private:
    std::function<void()> task_;
};

} // namespace wheel

#endif // __C_TASK_H__
