#include "Game.h"
#include "EntityManager.h"
#include "Globals.h"
#include "InputSystem.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "TimingSystem.h"
#include "UISystem.h"
#include "file_utils.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <json/json.h>

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

    load_map();

    RenderManager::get().enable_grid(true, 0, 0, 255, 255, 64, 64);
}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    TimingSystem::get().update(delta_f);

    RenderManager::get().update_animations(delta_f);

    PhysicsManager::get().simulate(delta_f);

    InputSystem::get().update();

    if (INPUT.KEY_W) {
        PhysicsManager::get().World().SetGravity({0.0f, 100.0f});
    }
    else if (INPUT.KEY_D) {
        PhysicsManager::get().World().SetGravity({100.0f, 0.0f});
    }
    else if (INPUT.KEY_S) {
        PhysicsManager::get().World().SetGravity({0.0f, -100.0f});
    }
    else if (INPUT.KEY_A) {
        PhysicsManager::get().World().SetGravity({-100.0f, 0.0f});
    }
    else {
        PhysicsManager::get().World().SetGravity({0.0f, 0.0f});
    }
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
    fixture_def.friction = 1.0f;

    body->CreateFixture(&fixture_def);

    body->ApplyTorque(1000000000.0f, true);

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

void Game::load_map()
{
    std::string const path = "./assets/tiles/grass_lands.map";
    auto file_contents = read_file(path);
    if (file_contents.first == nullptr) {
        std::cout << "Failed to load tilemap from: " << path << std::endl;
        return;
    }


    Json::CharReaderBuilder reader_builder;
    Json::CharReader* reader = reader_builder.newCharReader();
    Json::Value root;
    std::string err;

    if (!reader->parse(file_contents.first.get(), file_contents.first.get() + file_contents.second,
                       &root, &err)) {
        std::cout << "Failed to parse map file (" << path << "): " << err << std::endl;
    }
    else {
        int width = root["backdrop"]["size"]["w"].asInt();
        int height = root["backdrop"]["size"]["h"].asInt();

        std::string tile_path = "./assets/tiles/" + root["backdrop"]["tile"]["path"].asString();
        int tile_width = root["backdrop"]["tile"]["size"]["w"].asInt();
        int tile_height = root["backdrop"]["tile"]["size"]["h"].asInt();

        std::vector<SDL_Rect> tiles;
        tiles.resize(width * height);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                entity_t* entity = EntityManager::get().create_entity();
                entity->add_component(RENDER);

                auto render_comp =
                    RenderManager::get().create_static_render_component(entity, tile_path);
                render_comp->set_position(vec2f_t{static_cast<float>(x * tile_width),
                                                  static_cast<float>(y * tile_height)});
            }
        }

        // TODO we need to store tilemap in world space, not screen space!

        auto wall_array = root["walls"];
        for (auto& wall : wall_array) {
            int x = wall["coords"]["x"].asInt();
            int y = wall["coords"]["y"].asInt();
            std::string const texture_path = "./assets/tiles/" + wall["tile"]["path"].asString();
            int width = wall["tile"]["size"]["w"].asInt();
            int height = wall["tile"]["size"]["h"].asInt();

            entity_t* entity = EntityManager::get().create_entity();
            entity->add_component(RENDER | PHYSICS);

            auto render_comp =
                RenderManager::get().create_static_render_component(entity, texture_path);
            render_comp->set_position(vec2f_t{static_cast<float>(x), static_cast<float>(y)});

            b2BodyDef body_def = {};
            body_def.type = b2_staticBody;
            body_def.position.Set(static_cast<float>(x), static_cast<float>(y));
            b2Body* body = PhysicsManager::get().create_body(body_def);

            b2PolygonShape static_box = {};
            static_box.SetAsBox(static_cast<float>(width) / 2.0f,
                                static_cast<float>(height) / 2.0f);

            b2FixtureDef fixture_def = {};
            fixture_def.shape = &static_box;
            fixture_def.density = 1.0f;
            fixture_def.friction = 0.3f;

            body->CreateFixture(&fixture_def);

            auto physics_comp = PhysicsManager::get().create_component(entity);
            physics_comp->body = body;
            render_comp->physics_body = body;
        }
    }

    delete reader;
}
