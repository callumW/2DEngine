#include "TimingSystem.h"

#include <iostream>

TimingSystem& TimingSystem::get()
{
    static TimingSystem system;
    return system;
}

void TimingSystem::update(float delta)
{
    current_time += delta;

    for (auto it = tasks.begin(); it != tasks.end();) {
        auto task = it->second;
        float const delay = task.second;

        if (it->first + delay < current_time) {
            task.first(current_time - it->first);

            it = tasks.erase(it);
        }
        else {
            it++;
        }
    }
}
