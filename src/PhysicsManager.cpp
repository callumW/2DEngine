#include "PhysicsManager.h"
#include "Globals.h"

PhysicsManager::PhysicsManager() { physics_components.resize(NUM_OF_ENTITIES); }

PhysicsManager& PhysicsManager::get()
{
    static PhysicsManager phys_mgr;
    return phys_mgr;
}

void PhysicsManager::simulate(float delta)
{
    dirty_components.clear();
    size_t comp_count = physics_components.size();
    for (size_t i = 0; i < comp_count; i++) {
        physics_component_t& comp = physics_components[i];
        if (comp.net_force != vec2f_t::zero()) {
            comp.position += comp.net_force * delta;
            dirty_components.push_back(comp.owner_id);
        }
    }
}

physics_component_t* PhysicsManager::new_physics_component(entity_id_t id)
{
    static size_t max_size = physics_components.size();
    assert(id.index() < max_size);

    physics_components[id.index()].owner_id = id;

    return &physics_components[id.index()];
}

physics_component_t const* PhysicsManager::get_physics_component(entity_id_t id)
{
    return &physics_components[id.index()];
}
