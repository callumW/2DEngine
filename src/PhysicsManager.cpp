#include "PhysicsManager.h"
#include "Globals.h"

#include <iostream>

PhysicsManager& PhysicsManager::get()
{
    static PhysicsManager physics_manager;
    return physics_manager;
}

void PhysicsManager::simulate(float delta)
{
    size_t comp_count = components.size();
    for (size_t i = 0; i < comp_count; i++) {
        physics_component_t& comp = components[i];
        if (comp.net_force != vec2f_t::zero()) {
            comp.position += comp.net_force * delta;
        }

        if (comp.is_affected_by_gravity) {
            comp.position.y += PhysicsManager::GRAVITY * delta;
        }
    }
}
