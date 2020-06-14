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
#include <tmx.h>

#include <cmath>
#include <iostream>
#include <utility>


Game::Game() : world(gravity)
{
    InputSystem::mouse_click_callback_t spawn_func =
        std::bind(&Game::spawn_ball, this, std::placeholders::_1);

    InputSystem::get().on_mouse_left_click(spawn_func);

    load_map();

    RenderManager::get().enable_grid(true, 0, 0, 255, 126, 64, 64);
    PhysicsManager::get().World().SetGravity({0.0f, -100.0f});
}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    TimingSystem::get().update(delta_f);

    RenderManager::get().update_animations(delta_f);

    PhysicsManager::get().simulate(delta_f);

    InputSystem::get().update();

    update_player(delta_f);
}

void Game::spawn_ball(vec2f_t const& position)
{
    vec2f_t world_pos = RenderManager::get().convert_to_world_pos(position);
    entity_t* entity = EntityManager::get().create_entity();

    std::cout << "Spawning ball @ " << world_pos << std::endl;

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

static void create_tile(tmx_tile const* tile, unsigned int const tile_width,
                        unsigned int const tile_height, unsigned int const x, unsigned int const y)
{
    texture_t const* tex = static_cast<texture_t const*>(tile->image->resource_image);

    vec2f_t const pos{static_cast<float>(x) + (tile_width / 2.0f),
                      static_cast<float>(y) + (tile_height / 2.0f)};

    //
    // std::cout << "Creating tile @ " << pos << " | tex: " << *tex
    //           << " | Collision: " << (tile->collision == nullptr ? "n" : "y") << std::endl;

    entity_t* entity = EntityManager::get().create_entity();
    entity->add_component(RENDER);

    if (tile->collision != nullptr) {
        entity->add_component(PHYSICS);
    }

    auto render_comp = RenderManager::get().create_static_render_component(entity, *tex);
    render_comp->dst_rect.x = x;
    render_comp->dst_rect.y = y;
    render_comp->dst_rect.w = tile_width;
    render_comp->dst_rect.h = tile_height;
    render_comp->z_index = 0;

    if (tile->collision != nullptr) {
        vec2f_t world_pos = RenderManager::get().convert_to_world_pos(pos);
        world_pos +=
            {static_cast<float>(tile->collision->x), static_cast<float>(tile->collision->y)};
        auto physics_comp = PhysicsManager::get().create_component(entity);

        b2BodyDef body_def = {};
        body_def.type = b2_staticBody;
        body_def.position.Set(world_pos.x, world_pos.y);
        b2Body* body = PhysicsManager::get().create_body(body_def);

        b2PolygonShape dynamic_box = {};
        dynamic_box.SetAsBox(static_cast<float>(tile->collision->width) / 2.0f,
                             static_cast<float>(tile->collision->height) / 2.0f);

        b2FixtureDef fixture_def = {};
        fixture_def.shape = &dynamic_box;
        fixture_def.density = 1.0f;
        fixture_def.friction = 1.0f;

        body->CreateFixture(&fixture_def);

        render_comp->physics_body = body;
        physics_comp->body = body;
    }
}

void Game::load_map()
{

    tmx_img_load_func = tmx_load_texture;
    tmx_img_free_func = nullptr;

    tmx_map* map = tmx_load("./assets/movable_player_map.tmx");
    if (map == nullptr) {
        std::cout << "Failed to load tilemap!" << std::endl;
        return;
    }

    auto map_width = map->width;
    auto map_height = map->height;

    std::cout << "Loaded tilemap: " << std::endl
              << "width: " << map_width << std::endl
              << "height: " << map_height << std::endl
              << "tile width: " << map->tile_width << std::endl
              << "tile height: " << map->tile_height << std::endl;

    tmx_layer* layer = map->ly_head;

    while (layer != nullptr) {
        if (layer->type == L_LAYER) {
            for (int x = 0; x < map_width; x++) {
                for (int y = 0; y < map_height; y++) {
                    unsigned int gid =
                        (layer->content.gids[(y * map_width) + x]) & TMX_FLIP_BITS_REMOVAL;

                    if (gid != 0 && map->tiles[gid] != nullptr) {
                        create_tile(map->tiles[gid], map->tile_width, map->tile_height,
                                    x * map->tile_width, y * map->tile_height);
                    }
                }
            }
        }
        else if (layer->type == L_OBJGR) {
            auto object_group = layer->content.objgr;
            auto object = object_group->head;
            while (object != nullptr) {
                // if (object->type == OT_POINT) {
                if (strcmp("player_spawn", object->type) == 0) {
                    std::cout << "Found player spawn @ " << object->x << ", " << object->y
                              << std::endl;
                    spawn_player(
                        vec2f_t{static_cast<float>(object->x), static_cast<float>(object->y)});
                }
                // }

                object = object->next;
            }
        }

        layer = layer->next;
    }


    tmx_map_free(map);
}

void Game::spawn_player(vec2f_t const& position)
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

    render_comp->physics_body = body;
    physics_comp->body = body;

    player = entity;
}

void Game::update_player(float const delta)
{
    if (player == nullptr) {
        return;
    }
    if (INPUT.KEY_SPACE) {
        auto physics_comp = PhysicsManager::get().get_component(*player);
        assert(physics_comp != nullptr);

        physics_comp->body->ApplyLinearImpulseToCenter({0.0f, 150000.0f}, true);
    }
}
