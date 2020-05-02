#ifndef ENTITY_ID_H
#define ENTITY_ID_H

#include <cassert>
#include <cstdint>
#include <functional>
#include <ostream>
#include <set>
#include <utility>

size_t const MAX_NUM_ENTITIES = 1000000;

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

    entity_id_t() { idx = 0; }
    entity_id_t(entity_id_t const& other) { idx = other.idx; }
} entity_id_t;

bool operator==(entity_id_t const& lhs, entity_id_t const& rhs);

std::ostream& operator<<(std::ostream& stream, entity_id_t const& e);

typedef struct entity_id_hash_t {
    std::size_t operator()(entity_id_t const& id) const { return std::hash<int64_t>{}(id.idx); }
} entity_id_hash_t;

typedef struct entity_id_t_compare_t {
    bool operator()(entity_id_t const& lhs, entity_id_t const& rhs) const { return lhs == rhs; }
} entity_id_t_compare_t;

typedef struct entity_id_t_less_t {
    bool operator()(entity_id_t const& lhs, entity_id_t const& rhs) const
    {
        return lhs.idx < rhs.idx;
    }
} entity_id_t_less_t;

typedef std::set<entity_id_t, entity_id_t_less_t> entity_id_t_set_t;

typedef std::pair<entity_id_t, entity_id_t> entity_id_pair_t;

typedef struct entity_id_pair_t_less_t {
    bool operator()(entity_id_pair_t const& lhs, entity_id_pair_t const& rhs) const
    {
        return entity_id_t_less_t{}(lhs.first, rhs.second);
    }
} entity_id_pair_t_less_t;

typedef std::set<entity_id_pair_t, entity_id_pair_t_less_t> entity_id_t_pair_set_t;

#endif
