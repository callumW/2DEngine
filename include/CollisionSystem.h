#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <unordered_map>
#include <vector>

#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "ComponentManager.h"
#include "Entity.h"

class CollisionSystem : public ComponentManager<collision_component_t> {
public:
    void check_for_collisions();
};
#endif
