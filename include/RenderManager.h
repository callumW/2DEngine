#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "ComponentManager.h"
#include "RenderComponent.h"

class RenderManager : public ComponentManager<render_component_t> {
public:
    static RenderManager& get();

    void render_all();

    void update_animations(float delta);

    render_component_t* create_static_render_component(entity_t* entity,
                                                       std::string const& tex_path);
    render_component_t* create_animated_render_component(entity_t* entity,
                                                         std::string const& animation_path);

    vec2f_t convert_to_screen_space(vec2f_t const& world_pos);
    vec2f_t convert_to_world_pos(vec2f_t const& screen_pos);

    vec2f_t convert_to_screen_space(b2Vec2 const& world_pos);
    vec2f_t convert_to_world_pos(b2Vec2 const& screen_pos);

private:
    RenderManager() = default;

    texture_t update_animation(animation_t& animation);
};
#endif
