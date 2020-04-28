#ifndef ENTITY_ID_H
#define ENTITY_ID_H

#include <cassert>
#include <cstdint>
#include <functional>

size_t const MAX_NUM_ENTITIES = 50000;

int64_t const ENTITY_INDEX_BITS = 54;
int64_t const ENTITY_INDEX_MASK = (INT64_C(1) << ENTITY_INDEX_BITS) - 1;

int64_t const ENTITY_GENERATION_BITS = 10;
int64_t const ENTITY_GENERATION_MASK = (INT64_C(1) << ENTITY_GENERATION_BITS) - 1;

typedef struct entity_id_t {
    int64_t idx = 0;
    int64_t index() const { return idx & ENTITY_INDEX_MASK; }
    int64_t generation() const { return (idx >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

    void set_index(int64_t id)
    {
        assert(id <= ENTITY_INDEX_MASK);
        idx = (generation() << ENTITY_INDEX_BITS) | id;
    }

    void set_generation(int64_t gen)
    {
        assert(gen <= ENTITY_GENERATION_MASK);
        idx = (gen << ENTITY_INDEX_BITS) | index();
    }

    void increment_generation()
    {
        set_generation((generation() + 1) % (ENTITY_GENERATION_MASK + 1));
    }

} entity_id_t;

typedef struct entity_id_hash_t {
    std::size_t operator()(entity_id_t const& id) const { return std::hash<int64_t>{}(id.idx); }
} entity_id_hash_t;

typedef struct entity_id_t_compare_t {
    bool operator()(entity_id_t const& lhs, entity_id_t const& rhs) const
    {
        return lhs.idx == rhs.idx;
    }
} entity_id_t_compare_t;


#endif
