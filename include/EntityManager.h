#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Entity.h"
#include "Globals.h"
#include "entity_id.h"

#include <array>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

class EntityManager {
public:
    static EntityManager& get();

    Entity* find_entity(entity_id_t const id);

    inline bool has_entity(entity_id_t const id)
    {
        if (id.index() < next_free_space) {
            return id.generation() == entities[id.index()].id.generation();
        }
        else {
            std::cout << "Num entities is too small" << std::endl;
            return false;
        }
    }

    std::pair<entity_id_t, Entity*> new_entity();

    void schedule_destruction(entity_id_t const id);

    void update_dirty_entities(float delta);

    void render_entities();

    void process_dead_entities();

    void clear_dead_entities() { dead_entities.clear(); }
    void clear_moved_entities() { moved_entities.clear(); }

    entity_id_t_set_t const& get_dead_set() const { return dead_entities; }
    entity_id_t_pair_set_t const& get_moved_set() const { return moved_entities; }

private:
    EntityManager();

    void destroy_entity(entity_id_t const& e);

    size_t next_free_space = 0;
    std::vector<Entity> entities;

    entity_id_t_set_t marked_for_death;

    entity_id_t_set_t dead_entities;

    /*
        Set containg entitiy pairs which have been moved on the previous frame.

        The first element is the old id of the entity, the second element is the new id.
    */
    entity_id_t_pair_set_t moved_entities;
};

#endif
