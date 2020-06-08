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

    void enable_grid(bool enable, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0, int width = 0,
                     int height = 0);

private:
    RenderManager() = default;

    texture_t update_animation(animation_t& animation);

    void render_grid();

    bool grid_enabled = false;
    struct {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    } grid_color = {0};
    std::vector<std::pair<SDL_Point, SDL_Point>> grid_lines;
};
#endif
