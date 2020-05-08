#include "Game.h"
#include "CollisionSystem.h"
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
    InputSystem::mouse_click_callback_t spawn_func =
        std::bind(&Game::spawn_ball, this, std::placeholders::_1);

    InputSystem::get().on_mouse_left_click(spawn_func);
}

void Game::render() { render_manager.render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    PhysicsManager::get().simulate(delta_f);

    InputSystem::get().update();
}

void Game::spawn_ball(vec2f_t const& position)
{
    std::cout << "Spawn ball" << std::endl;
    auto entity = entity_manager.create_entity();

    auto physics_comp = PhysicsManager::get().create_component(entity);
    physics_comp->position = position;
    physics_comp->is_affected_by_gravity = true;

    auto render_comp = render_manager.create_component(entity);
    render_comp->texture = load_texture("./assets/bullet.bmp");
    render_comp->src_rect = {0, 0, 5, 5};
    render_comp->dst_rect = {static_cast<int>(position.x), static_cast<int>(position.y), 5, 5};
    render_comp->pivot_point = {2, 2};
}
