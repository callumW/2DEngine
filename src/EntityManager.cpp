#include "EntityManager.h"

EntityManager g_entity_manager;

std::weak_ptr<Entity> EntityManager::add_entity(Entity* entity)
{
    std::shared_ptr<Entity> ptr{entity};
    if (entity != nullptr) {
        entities.push_back(ptr);
    }
    return ptr;
}

void EntityManager::update(float delta)
{
    for (auto& entity : entities) {
        entity->update(delta);
    }
}

void EntityManager::cull()
{
    for (auto it = entities.begin(); it != entities.end();) {
        if (!(*it)->alive()) {
            it = entities.erase(it);
        }
        else {
            it++;
        }
    }
}
