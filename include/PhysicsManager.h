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
    static PhysicsManager& get();

    static constexpr float GRAVITY = 300.0f;

    void simulate(float delta);

private:
    PhysicsManager() = default;
};
#endif
