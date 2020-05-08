#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

RenderManager::RenderManager() {}

void RenderManager::render_all()
{
    size_t const num_components = components.size();
    for (size_t i = 0; i < num_components; i++) {
        render_component_t& render_comp = components[i];

        if (!render_comp.hidden) {
            render(render_comp);
        }
    }
}

void RenderManager::render(render_component_t& comp)
{
    // auto e = EntityManager::get().find_entity(comp.owner_id);

    // if (e == nullptr) {
    //     std::cout << "Got null entity when rendering: " << comp.owner_id.index() << std::endl;
    //     return;
    // }

    // comp.dst_rect.x = static_cast<int>(e->world_transform.position.x) - comp.src_rect.w / 2;
    // comp.dst_rect.y = static_cast<int>(e->world_transform.position.y) - comp.src_rect.h / 2;
    // comp.rotation = static_cast<double>(e->world_transform.rotation);

    SDL_RenderCopyEx(g_renderer, comp.texture, &comp.src_rect, &comp.dst_rect, comp.rotation,
                     &comp.pivot_point, comp.flip);
}
