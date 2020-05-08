#include "EntityManager.h"

entity_t* EntityManager::create_entity()
{
    entities.emplace_back(next_entity_uuid++);
    return &entities.back();
}
