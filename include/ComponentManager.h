#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "Entity.h"


#include <unordered_map>
#include <vector>

template<typename T>
class ComponentManager {
public:
    T* get_component(entity_t entity)
    {
        auto find_res = map.find(entity);

        if (find_res == map.end()) {
            return nullptr;
        }

        assert(entity == entities[find_res->second]);

        return &components[find_res->second];
    }

    T* create_component(entity_t* entity)
    {
        assert(map.find(*entity) == map.end());

        size_t const next_free_space = components.size();
        components.resize(next_free_space + 1);

        T* component = &components[next_free_space];
        entities.push_back(*entity);
        map[*entity] = next_free_space;

        return component;
    }

    void remove_component(entity_t entity)
    {
        auto find_res = map.find(entity);
        assert(find_res != map.end());

        size_t pos = find_res->second;

        size_t const end_pos = components.size() - 1;

        if (pos < end_pos && pos > 0) {
            auto swapped_entity = entities[end_pos];

            // update mapping for swapped entity
            map[swapped_entity] = pos;

            std::swap(components[end_pos], components[pos]);
            std::swap(entities[end_pos], entities[pos]);
        }

        map.erase(find_res);

        components.pop_back();
        entities.pop_back();
    }

    void update_component_mapping(entity_pair_t entity_update_pair)
    {
        auto const& new_id = entity_update_pair.first;
        auto const& old_id = entity_update_pair.second;

        auto find_res = map.find(old_id);

        assert(find_res != map.end());

        size_t pos = find_res->second;

        entities[pos] = new_id;

        map[new_id] = pos;
    }

protected:
    std::vector<T> components;
    std::vector<entity_t> entities;
    std::unordered_map<entity_t, size_t, entity_hash_t, entity_t_compare_t> map;
};
#endif
