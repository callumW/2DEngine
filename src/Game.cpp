#include "Game.h"
#include "EntityManager.h"
#include "Globals.h"
#include "InputSystem.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "TimingSystem.h"
#include "UISystem.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>

float const PLAYER_MOVEMENT_SPEED = 250.0f;
float const PLAYER_BULLET_SPEED = 1000.0f;
float const PLAYER_FIRE_RATE = 1.0f / 10.0f;


Game::Game()
{
    InputSystem::get().on_mouse_left_click([&](vec2f_t const& loc) { this->spawn_ball(loc); });
}

Game::~Game() {}

void Game::render()
{
    RenderManager::get().render_all();
    UISystem::get().render();
}

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    InputSystem::get().update();

    TimingSystem::get().update(delta_f);

    PhysicsManager::get().simulate(delta_f);

    EntityManager::get().update_dirty_entities(delta_f);
}

void Game::cleanup()
{
    EntityManager::get().clear_dead_entities();
    EntityManager::get().clear_moved_entities();

    EntityManager::get().process_dead_entities();

    PhysicsManager::get().cleanup();
    RenderManager::get().cleanup();
    TimingSystem::get().cleanup();
}

void Game::spawn_ball(vec2f_t const& loc)
{
    std::cout << "Spawn ball @ " << loc << std::endl;
    auto ball_pair = EntityManager::get().new_entity();

    auto ball = ball_pair.second;
    auto ball_id = ball_pair.first;

    assert(ball != nullptr);

    transform_t ball_world_transform;
    ball_world_transform.position = loc;
    ball->components |= RENDER;
    ball->set_world_transform(ball_world_transform);

    auto render_comp = RenderManager::get().new_render_component();
    render_comp->owner_id = ball_id;
    render_comp->texture = load_texture("./assets/bullet.bmp");
    render_comp->src_rect.w = 5;
    render_comp->src_rect.h = 5;
    render_comp->dst_rect = render_comp->src_rect;
    render_comp->dst_rect.x = static_cast<int>(loc.x) - 2;
    render_comp->dst_rect.y = static_cast<int>(loc.y) - 2;
    render_comp->pivot_point = {2, 2};

    auto physics_comp = PhysicsManager::get().new_physics_component(ball_id);
    physics_comp->position = loc;
    physics_comp->is_affected_by_gravity = true;
}
