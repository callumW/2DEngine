#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include <vector>

#include "Entity.h"

class EntityManager {
public:
    std::weak_ptr<Entity> add_entity(Entity* entity);

    void update(float delta);
    void cull();
    void render();

private:
    std::vector<std::shared_ptr<Entity>> entities;
};

extern EntityManager g_entity_manager;
#endif
