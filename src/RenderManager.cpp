#include <iostream>

#include "EntityManager.h"
#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

RenderManager::RenderManager() { render_components.resize(1000000); }

RenderManager& RenderManager::get()
{
    static RenderManager mgr;
    return mgr;
}

void RenderManager::render_all()
{
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
