#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include <array>
#include <unordered_map>
#include <vector>

#include "ComponentManager.h"
#include "Entity.h"
#include "PhysicsComponent.h"

class PhysicsManager : public ComponentManager<physics_component_t> {
public:
    typedef struct move_record_t {
        entity_t entity;
        vec2f_t old_pos;
        vec2f_t new_pos;
    } move_record_t;

    static PhysicsManager& get();

    static constexpr float GRAVITY = 300.0f;

    void simulate(float delta);


    std::vector<std::pair<entity_t, vec2f_t*>> const& get_dirty_positions()
    {
        return dirty_positions;
    }

private:
    PhysicsManager() = default;

    std::vector<std::pair<entity_t, vec2f_t*>> dirty_positions;
};
#endif
