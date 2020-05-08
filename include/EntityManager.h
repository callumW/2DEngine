#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <list>

#include "ComponentTypes.h"
#include "Entity.h"

class EntityManager {
public:
    static EntityManager& get();

    entity_t* create_entity();

    void destroy_entity(entity_t const& entity);

private:
    EntityManager() = default;

    int64_t next_entity_uuid = 1;

    std::list<entity_t> entities;
};
#endif
