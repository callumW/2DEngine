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
#include <utility>

float const PLAYER_MOVEMENT_SPEED = 250.0f;
float const PLAYER_BULLET_SPEED = 1000.0f;
float const PLAYER_FIRE_RATE = 1.0f / 10.0f;

Game::Game()
{
    InputSystem::mouse_click_callback_t spawn_func =
        std::bind(&Game::spawn_ball, this, std::placeholders::_1);

    InputSystem::get().on_mouse_left_click(spawn_func);

    entity_t* floor = EntityManager::get().create_entity();

    floor->add_component(COLLISION);

    auto collision_comp = CollisionSystem::get().create_component(floor);
    collision_comp->box = {0.0f, static_cast<float>(WINDOW_HEIGHT),
                           static_cast<float>(WINDOW_WIDTH), 40.0f};

    collision_comp->is_static = true;
}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    TimingSystem::get().update(delta_f);

    PhysicsManager::get().simulate(delta_f);
    CollisionSystem::get().check_for_collisions();

    InputSystem::get().update();
}

void Game::spawn_ball(vec2f_t const& position)
{
    entity_t* entity = EntityManager::get().create_entity();

    entity->add_component(PHYSICS | RENDER | COLLISION);

    auto physics_comp = PhysicsManager::get().create_component(entity);
    physics_comp->position = position;
    physics_comp->is_affected_by_gravity = true;

    auto render_comp = RenderManager::get().create_render_component(entity, "./assets/bullet.bmp");
    render_comp->set_position(position);

    auto collision_comp = CollisionSystem::get().create_component(entity);
    collision_comp->box = {position.x - 2.0f, position.y - 2.0f, 5.0f, 5.0f};
    collision_comp->is_static = false;


    assert(entity->has_component(RENDER));
    assert(entity->has_component(PHYSICS));
    assert(entity->has_component(COLLISION));

    // TimingSystem::timer_task_cb_t delete_func = [entity](float delta) {
    //     EntityManager::get().destroy_entity(*entity);
    // };
    //
    // auto delete_task = std::make_pair(delete_func, 1.0f);
    // TimingSystem::get().schedule_task(delete_task);
}
