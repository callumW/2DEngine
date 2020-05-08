#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <vector>

#include "ComponentTypes.h"
#include "Entity.h"

class EntityManager {
public:
    EntityManager() = default;

    entity_t* create_entity();

private:
    int64_t next_entity_uuid = 1;

    std::vector<entity_t> entities;
};
#endif
