#include "PhysicsManager.h"
#include "Globals.h"
#include "UISystem.h"

#include <iostream>
#include <sstream>

PhysicsManager& PhysicsManager::get()
{
    static PhysicsManager physics_manager;
    return physics_manager;
}

void PhysicsManager::simulate(float delta)
{
    world.Step(delta, 8, 3);
    std::stringstream str_stream;
    str_stream << "Physics Body Count: " << world.GetBodyCount();

    UISystem::get().add_dynamic_text(SDL_Point{0, 16}, str_stream.str());
}

void PhysicsManager::pre_remove(physics_component_t* component)
{
    if (component && component->body) {
        world.DestroyBody(component->body);
    }
}
