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
#include <utility>

float const PLAYER_MOVEMENT_SPEED = 250.0f;
float const PLAYER_BULLET_SPEED = 1000.0f;
float const PLAYER_FIRE_RATE = 1.0f / 10.0f;

Game::Game() : world(gravity)
{
    InputSystem::mouse_click_callback_t spawn_func =
        std::bind(&Game::spawn_ball, this, std::placeholders::_1);

    InputSystem::get().on_mouse_left_click(spawn_func);
}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    TimingSystem::get().update(delta_f);

    RenderManager::get().update_animations(delta_f);

    PhysicsManager::get().simulate(delta_f);

    InputSystem::get().update();
}

void Game::spawn_ball(vec2f_t const& position)
{
    vec2f_t world_pos = RenderManager::get().convert_to_world_pos(position);
    entity_t* entity = EntityManager::get().create_entity();

    entity->add_component(RENDER | PHYSICS);

    auto render_comp = RenderManager::get().create_animated_render_component(
        entity, "./assets/sprite-0001/Sprite-0001.json");
    render_comp->set_position(world_pos);

    auto physics_comp = PhysicsManager::get().create_component(entity);

    b2BodyDef body_def = {};
    body_def.type = b2_dynamicBody;
    body_def.position.Set(world_pos.x, world_pos.y);
    b2Body* body = PhysicsManager::get().create_body(body_def);

    b2PolygonShape dynamic_box = {};
    dynamic_box.SetAsBox(static_cast<float>(render_comp->texture.width()) / 2.0f,
                         static_cast<float>(render_comp->texture.height()) / 2.0f);

    b2FixtureDef fixture_def = {};
    fixture_def.shape = &dynamic_box;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;

    body->CreateFixture(&fixture_def);

    render_comp->physics_body = body;
    physics_comp->body = body;

    assert(entity->has_component(RENDER));
    assert(entity->has_component(PHYSICS));

    // TimingSystem::timer_task_cb_t delete_func = [entity](float delta) {
    //     EntityManager::get().destroy_entity(*entity);
    // };
    //
    // auto delete_task = std::make_pair(delete_func, 3.0f);
    // TimingSystem::get().schedule_task(delete_task);
}
