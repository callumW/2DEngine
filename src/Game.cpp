#include "Game.h"
#include "EntityManager.h"
#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>

float const PLAYER_MOVEMENT_SPEED = 250.0f;
float const PLAYER_BULLET_SPEED = 100.0f;
float const PLAYER_FIRE_RATE = 1.0f / 10.0f;
;

Game::Game()
{
    auto player_pair = EntityManager::get().new_entity();
    assert(player_pair.second != nullptr);
    m_player_id = player_pair.first;

    auto render_comp = RenderManager::get().new_render_component();

    render_comp->entity_id = m_player_id;
    render_comp->texture = load_texture("./assets/G.bmp");
    render_comp->dst_rect.w = 40;
    render_comp->dst_rect.h = 40;
    render_comp->src_rect = render_comp->dst_rect;
    render_comp->pivot_point = {render_comp->src_rect.w / 2, render_comp->src_rect.h / 2};
}

Game::~Game() {}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    update_player(delta_f);

    PhysicsManager::get().simulate(delta_f);

    EntityManager::get().update_dirty_entities(delta_f);
}

void Game::update_player(float delta)
{
    auto player = EntityManager::get().find_entity(m_player_id);
    assert(player != nullptr);
    if (INPUT.KEY_W) {
        player->world_transform.position.y -= PLAYER_MOVEMENT_SPEED * delta;
    }
    else if (INPUT.KEY_S) {
        player->world_transform.position.y += PLAYER_MOVEMENT_SPEED * delta;
    }

    if (INPUT.KEY_A) {
        player->world_transform.position.x -= PLAYER_MOVEMENT_SPEED * delta;
    }
    else if (INPUT.KEY_D) {
        player->world_transform.position.x += PLAYER_MOVEMENT_SPEED * delta;
    }

    vec2f_t mouse_pos = {static_cast<float>(INPUT.mouse_x), static_cast<float>(INPUT.mouse_y)};

    player->face(mouse_pos);

    static float time_since_last_fire = 99999.0f;

    if (INPUT.mouse_left_click && time_since_last_fire > PLAYER_FIRE_RATE) {
        time_since_last_fire = 0.0f;
        vec2f_t const force =
            (mouse_pos - player->world_transform.position).normalised() * PLAYER_BULLET_SPEED;

        fire_bullet(player->world_transform.position, force);
    }
    else {
        time_since_last_fire += delta;
    }
}

void Game::fire_bullet(vec2f_t const& loc, vec2f_t const& force)
{
    auto bullet_pair = EntityManager::get().new_entity();

    auto bullet_ent = bullet_pair.second;

    assert(bullet_ent != nullptr);

    // need physics
    // needs render component

    auto render_comp = RenderManager::get().new_render_component();
    render_comp->entity_id = bullet_pair.first;
    render_comp->texture = load_texture("./assets/bullet.bmp");
    render_comp->src_rect.w = 5;
    render_comp->src_rect.h = 5;
    render_comp->dst_rect = render_comp->src_rect;
    render_comp->dst_rect.x = static_cast<int>(loc.x) - 2;
    render_comp->dst_rect.y = static_cast<int>(loc.y) - 2;
    render_comp->pivot_point = {2, 2};

    auto physics_comp = PhysicsManager::get().new_physics_component(bullet_pair.first);
    physics_comp->position = loc;
    physics_comp->net_force = force;
}
