#ifndef ENTITY_H
#define ENTITY_H

#include <cassert>
#include <cstdint>
#include <functional>
#include <ostream>
#include <set>
#include <utility>

#include "ComponentTypes.h"

size_t const MAX_NUM_ENTITIES = 1000000;

int64_t const ENTITY_INDEX_BITS = 54;
int64_t const ENTITY_INDEX_MASK = (INT64_C(1) << ENTITY_INDEX_BITS) - 1;

int64_t const ENTITY_GENERATION_BITS = 10;
int64_t const ENTITY_GENERATION_MASK = (INT64_C(1) << ENTITY_GENERATION_BITS) - 1;

typedef struct entity_t {
    int64_t uuid = 0;
    COMPONENT_TYPE components = 0;

    inline bool has_component(COMPONENT_TYPE comp) const { return components & comp; }

    entity_t(int64_t new_uuid) { uuid = new_uuid; }
} entity_t;

bool operator==(entity_t const& lhs, entity_t const& rhs);

std::ostream& operator<<(std::ostream& stream, entity_t const& e);

typedef struct entity_hash_t {
    std::size_t operator()(entity_t const& id) const { return std::hash<int64_t>{}(id.uuid); }
} entity_hash_t;

typedef struct entity_t_compare_t {
    bool operator()(entity_t const& lhs, entity_t const& rhs) const { return lhs == rhs; }
} entity_t_compare_t;

typedef struct entity_t_less_t {
    bool operator()(entity_t const& lhs, entity_t const& rhs) const { return lhs.uuid < rhs.uuid; }
} entity_t_less_t;

typedef std::set<entity_t, entity_t_less_t> entity_set_t;

typedef std::pair<entity_t, entity_t> entity_pair_t;

typedef struct entity_pair_t_less_t {
    bool operator()(entity_pair_t const& lhs, entity_pair_t const& rhs) const
    {
        return entity_t_less_t{}(lhs.first, rhs.second);
    }
} entity_pair_t_less_t;

typedef std::set<entity_pair_t, entity_pair_t_less_t> entity_pair_set_t;

#endif
