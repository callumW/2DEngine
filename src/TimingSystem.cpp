#include "TimingSystem.h"
#include "EntityManager.h"

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

void TimingSystem::check_for_invalidated_entities()
{
    for (auto it = tasks.begin(); it != tasks.end();) {
        auto const& id = std::get<2>(it->second);

        bool removed = false;
        for (auto const& removed_record : EntityManager::get().get_dead_set()) {
            if (removed_record == id) {
                removed = true;
                it = tasks.erase(it);
                break;
            }
        }

        if (removed) {
            continue;
        }

        for (auto const& move_record : EntityManager::get().get_moved_set()) {
            if (move_record.first == id) {
                it->second = timer_task_t{std::get<0>(it->second), std::get<1>(it->second),
                                          move_record.second};
                break;
            }
        }

        it++;
    }
}

void TimingSystem::cleanup() { check_for_invalidated_entities(); }
