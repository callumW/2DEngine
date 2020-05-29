#include "PhysicsManager.h"
#include "Globals.h"

#include <iostream>

PhysicsManager& PhysicsManager::get()
{
    static PhysicsManager physics_manager;
    return physics_manager;
}

void PhysicsManager::simulate(float delta) { world.Step(delta, 8, 3); }

void PhysicsManager::pre_remove(physics_component_t* component)
{
    if (component && component->body) {
        world.DestroyBody(component->body);
    }
}
