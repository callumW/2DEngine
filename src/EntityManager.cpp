#include "EntityManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"


EntityManager& EntityManager::get()
{
    static EntityManager manager;
    return manager;
}

entity_t* EntityManager::create_entity()
{
    entity_t e{next_entity_uuid++};
    entities.push_back(e);
    return &entities.back();
}

void EntityManager::destroy_entity(entity_t const& entity)
{

    if (entity.components & RENDER) {
        RenderManager::get().remove_component(entity);
    }
    if (entity.components & PHYSICS) {
        PhysicsManager::get().remove_component(entity);
    }
    if (entity.components & ANIMATION) {
    }
    auto find_res = std::find(entities.begin(), entities.end(), entity);
    assert(find_res != entities.end());

    entities.erase(find_res);
}
