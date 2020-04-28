#include <iostream>

#include "EntityManager.h"
#include "Globals.h"
#include "RenderManager.h"

RenderManager& RenderManager::get()
{
    static RenderManager mgr;
    return mgr;
}

void RenderManager::render_all()
{
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
    auto entity = EntityManager::get().find_entity(comp.entity_id);
    if (entity) {
        comp.dst_rect.x = static_cast<int>(entity->world_transform.position.x);
        comp.dst_rect.y = static_cast<int>(entity->world_transform.position.y);
    }

    SDL_RenderCopyEx(g_renderer, comp.texture, &comp.src_rect, &comp.dst_rect, comp.rotation,
                     &comp.pivot_point, comp.flip);
}
