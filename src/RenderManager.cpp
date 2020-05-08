#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

RenderManager::RenderManager() {}

void RenderManager::render_all()
{
    size_t const num_components = components.size();
    for (size_t i = 0; i < num_components; i++) {
        render_component_t& comp = components[i];

        if (!comp.hidden) {

            auto physics_comp = PhysicsManager::get().get_component(entities[i]);
            if (physics_comp) {
                comp.dst_rect.x = static_cast<int>(physics_comp->position.x);
                comp.dst_rect.y = static_cast<int>(physics_comp->position.y);
            }

            SDL_RenderCopyEx(g_renderer, comp.texture, &comp.src_rect, &comp.dst_rect,
                             comp.rotation, &comp.pivot_point, comp.flip);
        }
    }
}
