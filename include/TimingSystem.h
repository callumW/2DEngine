#ifndef TIMING_SYSTEM_H
#define TIMING_SYSTEM_H

#include "Entity.h"

#include <functional>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

class TimingSystem {
public:
    static TimingSystem& get();

    /* timer callback, takes a float which is the number of seconds that has passed since task
        was added. */
    typedef std::function<void(float)> timer_task_cb_t;

    /* pair of wait time & callback to execute after wait time */
    typedef std::pair<timer_task_cb_t, float> timer_task_t;
    void schedule_task(timer_task_t& task) { tasks.push_back({current_time, task}); }


    void update(float delta);

    void cleanup();

private:
    TimingSystem() = default;

    std::vector<std::pair<float, timer_task_t>> tasks;
    float current_time = 0.0f;
};
#endif
