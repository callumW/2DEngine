#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "loading_helpers.h"

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

            if (entities[i].has_component(PHYSICS)) {
                auto physics_comp = PhysicsManager::get().get_component(entities[i]);
                if (physics_comp && physics_comp->body) {
                    comp.set_position(physics_comp->body->GetWorldCenter());
                }
            }

            SDL_RenderCopyEx(g_renderer, comp.texture.tex, &comp.texture.src_rect, &comp.dst_rect,
                             comp.rotation, &comp.pivot_point, comp.flip);
        }
    }
}

render_component_t* RenderManager::create_render_component(entity_t* entity,
                                                           std::string const& tex_path)
{
    render_component_t* comp = create_component(entity);

    comp->texture = load_texture(tex_path);
    comp->pivot_point = {comp->texture.src_rect.w / 2, comp->texture.src_rect.h / 2};
    comp->dst_rect = comp->texture.src_rect;

    return comp;
}
