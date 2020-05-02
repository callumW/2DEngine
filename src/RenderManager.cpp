#include <iostream>

#include "EntityManager.h"
#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

RenderManager::RenderManager() { render_components.resize(NUM_OF_ENTITIES); }

RenderManager& RenderManager::get()
{
    static RenderManager mgr;
    return mgr;
}

void RenderManager::render_all()
{
    check_for_dead_entities();
    update_dirty_positions();

    for (size_t i = 0; i < first_free_render_component; i++) {
        render_component_t& render_comp = render_components[i];

        if (!render_comp.hidden) {
            render(render_comp);
        }
    }
}

render_component_t* RenderManager::new_render_component()
{
    assert(first_free_render_component < MAX_NUM_ENTITIES);

    return &render_components[first_free_render_component++];
}

void RenderManager::render(render_component_t& comp)
{
    auto e = EntityManager::get().find_entity(comp.owner_id);

    if (e == nullptr) {
        std::cout << "Got null entity when rendering: " << comp.owner_id.index() << std::endl;
        return;
    }

    comp.dst_rect.x = static_cast<int>(e->world_transform.position.x) - comp.src_rect.w / 2;
    comp.dst_rect.y = static_cast<int>(e->world_transform.position.y) - comp.src_rect.h / 2;
    comp.rotation = static_cast<double>(e->world_transform.rotation);

    SDL_RenderCopyEx(g_renderer, comp.texture, &comp.src_rect, &comp.dst_rect, comp.rotation,
                     &comp.pivot_point, comp.flip);
}

void RenderManager::update_dirty_positions()
{
    auto const& dirties = PhysicsManager::get().dirty_entities();

    for (auto& e : dirties) {
        assert(e.index() < first_free_render_component);
        auto entity = EntityManager::get().find_entity(e);
        if (entity) {
            render_components[e.index()].dst_rect.x =
                static_cast<int>(entity->world_transform.position.x);
            render_components[e.index()].dst_rect.y =
                static_cast<int>(entity->world_transform.position.y);
        }
    }
}

void RenderManager::check_for_dead_entities()
{
    auto const& dead_ents = EntityManager::get().get_dead_set();

    for (auto& dead : dead_ents) {

        size_t dead_pos = dead.index();

        // need to remove entity
        render_components[dead_pos].reset();
        first_free_render_component--;
    }

    for (auto& entity_pair : EntityManager::get().get_moved_set()) {
        render_components[entity_pair.first.index()].owner_id = entity_pair.second;
        std::swap(render_components[entity_pair.first.index()],
                  render_components[entity_pair.second.index()]);
    }
}
