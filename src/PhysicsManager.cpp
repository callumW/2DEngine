#include "PhysicsManager.h"

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
    assert(map.find(id) == map.end());

    physics_component_t comp;
    comp.owner_id = id;
    physics_components.push_back(comp);

    auto idx = physics_components.size() - 1;

    map.insert({id, idx});

    return &physics_components[idx];
}

physics_component_t const* PhysicsManager::get_physics_component(entity_id_t id)
{
    physics_component_t const* ret = nullptr;
    auto const res = map.find(id);
    if (res != map.end()) {
        ret = &physics_components[res->second];
    }
    return ret;
}
