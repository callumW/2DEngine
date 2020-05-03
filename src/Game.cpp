#include "Game.h"
#include "CollisionSystem.h"
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

    auto floor_pair = EntityManager::get().new_entity();

    auto floor = floor_pair.second;
    auto floor_id = floor_pair.first;

    assert(floor != nullptr);

    transform_t transform;
    transform.position = {static_cast<float>(WINDOW_WIDTH) / 2.0f,
                          static_cast<float>(WINDOW_HEIGHT)};
    floor->set_world_transform(transform);
    floor->components |= RENDER | COLLISION;

    auto render_comp = RenderManager::get().new_render_component();
    render_comp->owner_id = floor_id;
    render_comp->texture = nullptr;
    render_comp->hidden = true;

    auto collision_comp = CollisionSystem::get().new_collision_component(floor_id);
    collision_comp->box = {0.0f, transform.position.y, static_cast<float>(WINDOW_WIDTH), 10.0f};

    collision_comp->on_collide = []() { std::cout << "floor collides!" << std::endl; };
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

    CollisionSystem::get().check_for_collisions();

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
    auto ball_pair = EntityManager::get().new_entity();

    auto ball = ball_pair.second;
    auto ball_id = ball_pair.first;

    assert(ball != nullptr);

    transform_t ball_world_transform;
    ball_world_transform.position = loc;
    ball->components |= RENDER | PHYSICS | COLLISION;
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

    auto collision_comp = CollisionSystem::get().new_collision_component(ball_id);
    collision_comp->box = {
        static_cast<float>(render_comp->dst_rect.x), static_cast<float>(render_comp->dst_rect.y),
        static_cast<float>(render_comp->dst_rect.w), static_cast<float>(render_comp->dst_rect.h)};
}
