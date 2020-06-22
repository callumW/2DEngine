#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "TextureLoader.h"
#include "loading_helpers.h"

RenderManager& RenderManager::get()
{
    static RenderManager render_manager;
    return render_manager;
}


void RenderManager::render_all()
{
    if (background_enabled) {
        render_bg();
    }
    size_t const num_components = components.size();
    for (size_t level = 0; level < 2; level++) {
        for (size_t i = 0; i < num_components; i++) {
            render_component_t& comp = components[i];
            SDL_Point* debug_points = nullptr;
            int point_count = 0;
            if (!comp.hidden && comp.z_index == level) {

                if (entities[i].has_component(PHYSICS)) {
                    auto physics_comp = PhysicsManager::get().get_component(entities[i]);
                    if (physics_comp && physics_comp->body) {
                        auto physics_pos = physics_comp->body->GetWorldCenter();
                        comp.set_position(convert_to_screen_space(physics_pos));
                        comp.rotation = physics_comp->body->GetAngle();

                        if (SHOW_COLLISION_DEBUG) {
                            auto fixture = physics_comp->body->GetFixtureList();
                            if (fixture) {
                                b2PolygonShape* shape = (b2PolygonShape*) fixture->GetShape();
                                if (shape) {
                                    point_count = shape->m_count;
                                    debug_points = new SDL_Point[point_count + 1];
                                    for (int i = 0; i < point_count; i++) {
                                        auto vec = convert_to_screen_space(shape->m_vertices[i] +
                                                                           physics_pos);
                                        debug_points[i] = {static_cast<int>(vec.x),
                                                           static_cast<int>(vec.y)};
                                    }
                                    debug_points[point_count] = debug_points[0];
                                    point_count += 1;
                                }
                            }
                        }
                    }
                }

                SDL_RenderCopyEx(g_renderer, comp.texture.tex, &comp.texture.src_rect,
                                 &comp.dst_rect, comp.rotation, &comp.pivot_point, comp.flip);

                if (debug_points != nullptr) {
                    SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLines(g_renderer, debug_points, point_count);

                    delete[] debug_points;
                    debug_points = nullptr;
                }
            }
        }
    }

    if (grid_enabled) {
        render_grid();
    }
}

void RenderManager::update_animations(float delta)
{
    size_t const num_components = components.size();
    for (size_t i = 0; i < num_components; i++) {
        render_component_t& comp = components[i];
        if (comp.is_animated) {
            auto& animation = comp.animation;
            animation.cur_time += delta;
            comp.texture = update_animation(animation);
        }
    }
}

texture_t RenderManager::update_animation(animation_t& animation)
{
    if (animation.frames[animation.cur_pos].duration < animation.cur_time) {
        animation.cur_time -= animation.frames[animation.cur_pos].duration;
        animation.cur_pos = (animation.cur_pos + 1) % animation.frames.size();
        return update_animation(animation);
    }
    else {
        return animation.frames[animation.cur_pos].texture;
    }
}

render_component_t* RenderManager::create_static_render_component(entity_t* entity,
                                                                  std::string const& tex_path)
{
    render_component_t* comp = create_component(entity);

    comp->texture = load_texture(tex_path);
    comp->pivot_point = {comp->texture.src_rect.w / 2, comp->texture.src_rect.h / 2};
    comp->dst_rect = comp->texture.src_rect;
    comp->is_animated = false;

    return comp;
}

render_component_t* RenderManager::create_static_render_component(entity_t* entity, texture_t tex)
{
    render_component_t* comp = create_component(entity);

    comp->texture = tex;
    comp->pivot_point = {comp->texture.src_rect.w / 2, comp->texture.src_rect.h / 2};
    comp->dst_rect = comp->texture.src_rect;
    comp->is_animated = false;

    return comp;
}

render_component_t*
RenderManager::create_animated_render_component(entity_t* entity, std::string const& animation_path)
{
    render_component_t* comp = create_component(entity);
    comp->is_animated = true;

    assert(TextureLoader::get().load_animation_frames(animation_path, comp->animation));

    comp->texture = comp->animation.frames[0].texture;
    comp->pivot_point = {comp->texture.src_rect.w / 2 + comp->texture.src_rect.x,
                         comp->texture.src_rect.h / 2 + comp->texture.src_rect.y};
    comp->dst_rect = comp->texture.src_rect;

    return comp;
}

vec2f_t RenderManager::convert_to_screen_space(vec2f_t const& world_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH) / RENDER_SCALE_FACTOR;
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT) / RENDER_SCALE_FACTOR;
    static vec2f_t view_port_top_left = {0.0f - viewport_width / 2.0f,
                                         0.0f - viewport_height / 2.0f};
    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return vec2f_t{world_pos.x - view_port_top_left.x, (0 - world_pos.y) - view_port_top_left.y} *
           RENDER_SCALE_FACTOR;
}
vec2f_t RenderManager::convert_to_world_pos(vec2f_t const& screen_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);

    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return vec2f_t{screen_pos.x - world_center.x, 0 - (screen_pos.y - world_center.y)} /
           RENDER_SCALE_FACTOR;
}

vec2f_t RenderManager::convert_to_screen_space(b2Vec2 const& world_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH) / RENDER_SCALE_FACTOR;
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT) / RENDER_SCALE_FACTOR;
    static vec2f_t view_port_top_left = {0.0f - viewport_width / 2.0f,
                                         0.0f - viewport_height / 2.0f};

    return vec2f_t{world_pos.x - view_port_top_left.x, (0 - world_pos.y) - view_port_top_left.y} *
           RENDER_SCALE_FACTOR;
}
vec2f_t RenderManager::convert_to_world_pos(b2Vec2 const& screen_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);

    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return vec2f_t{screen_pos.x - world_center.x, 0 - (screen_pos.y - world_center.y)} /
           RENDER_SCALE_FACTOR;
}

void RenderManager::enable_grid(bool enable, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int width,
                                int height)
{
    grid_enabled = enable;
    if (!enable) {
        grid_lines.clear();
    }
    else {
        assert(width > 0 && height > 0);
        for (int x = 0; x < WINDOW_WIDTH; x += width) {
            grid_lines.push_back(std::make_pair(SDL_Point{x, 0}, SDL_Point{x, WINDOW_HEIGHT}));
        }

        for (int y = 0; y < WINDOW_HEIGHT; y += height) {
            grid_lines.push_back(std::make_pair(SDL_Point{0, y}, SDL_Point{WINDOW_WIDTH, y}));
        }

        grid_color = {r, g, b, a};
    }
}

void RenderManager::render_grid()
{
    SDL_SetRenderDrawColor(g_renderer, grid_color.r, grid_color.g, grid_color.b, grid_color.a);
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
    for (auto& line : grid_lines) {
        SDL_RenderDrawLine(g_renderer, line.first.x, line.first.y, line.second.x, line.second.y);
    }
}

void RenderManager::enable_background(bool enable, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    background_enabled = enable;
    bg_color = {r, g, b, a};
}

void RenderManager::render_bg()
{
    SDL_SetRenderDrawColor(g_renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(g_renderer);
}
