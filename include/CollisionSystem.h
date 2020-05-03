#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <unordered_map>
#include <vector>

#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "entity_id.h"

class CollisionSystem {
public:
    static CollisionSystem& get();

    void cleanup();

    collision_component_t* new_collision_component(entity_id_t const& id);

    collision_component_t* get_collision_component(entity_id_t const& id);

    void check_for_collisions();

    void update_dirty_colliders();

private:
    CollisionSystem() = default;

    void check_for_moved_entities();
    void check_for_dead_entities();

    void update_entity_mapping(entity_id_t const& old_id, entity_id_t const& new_id);

    void validate_map();

    void verify_removed(entity_id_t const& id);

    std::unordered_map<entity_id_t, size_t, entity_id_hash_t, entity_id_t_compare_t> map;
    std::vector<collision_component_t> components;
};
#endif
