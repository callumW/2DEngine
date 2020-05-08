#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"

RenderManager& RenderManager::get()
{
    static RenderManager render_manager;
    return render_manager;
}


void RenderManager::render_all()
{
    size_t const num_components = components.size();
    for (size_t i = 0; i < num_components; i++) {
        render_component_t& comp = components[i];

        if (!comp.hidden) {

            auto physics_comp = PhysicsManager::get().get_component(entities[i]);
            if (physics_comp) {
                comp.dst_rect.x = static_cast<int>(physics_comp->position.x) - comp.src_rect.w / 2;
                comp.dst_rect.y = static_cast<int>(physics_comp->position.y) - comp.src_rect.h / 2;
            }

            SDL_RenderCopyEx(g_renderer, comp.texture, &comp.src_rect, &comp.dst_rect,
                             comp.rotation, &comp.pivot_point, comp.flip);
        }
    }
}

render_component_t* RenderManager::create_component(entity_t* entity)
{
    entity->components |= RENDER;
    return ComponentManager::create_component(entity);
}
