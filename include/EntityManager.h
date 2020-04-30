#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Entity.h"
#include "Globals.h"
#include "entity_id.h"

#include <array>
#include <set>
#include <utility>
#include <vector>

class EntityManager {
public:
    static EntityManager& get();

    Entity* find_entity(entity_id_t const id);

    inline bool has_entity(entity_id_t const id)
    {
        return id.generation() == entities[id.index()].id.generation();
    }

    std::pair<entity_id_t, Entity*> new_entity();

    void schedule_destruction(entity_id_t const id);

    void update_dirty_entities(float delta);
    void update_all_entities(float delta);


    void render_entities();

    void process_dead_entities();


    std::set<entity_id_t, entity_id_t_less_t> const& get_dead_set() const { return dead_entities; }

private:
    EntityManager();

    void destroy_entity(entity_id_t const& e);

    size_t next_free_space = 0;
    std::vector<Entity> entities;

    std::set<entity_id_t, entity_id_t_less_t> dead_entities;
};

#endif
