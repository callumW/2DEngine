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
        auto delay = std::get<0>(it->second);

        if (it->first + delay < current_time) {
            auto callback = std::get<1>(it->second);
            auto id = std::get<2>(it->second);

            callback(current_time - it->first, id);

            it = tasks.erase(it);
        }
        else {
            it++;
        }
    }
}
