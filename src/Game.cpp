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


Game::Game()
{

    for (auto& e : entities) {
        auto new_entity = EntityManager::get().new_entity();

        auto render_comp = RenderManager::get().new_render_component();
        render_comp->entity_id = new_entity.first;
        render_comp->hidden = false;
        render_comp->texture = load_default_texture();
        render_comp->src_rect.w = 40;
        render_comp->src_rect.h = 40;
        render_comp->dst_rect = render_comp->src_rect;
        render_comp->pivot_point = {20, 20};

        auto physics = PhysicsManager::get().new_physics_component(new_entity.first);
        physics->net_force = {10.0f, 10.0f};
        e = new_entity.first;
    }
}

Game::~Game() {}

void Game::render() { RenderManager::get().render_all(); }

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;

    PhysicsManager::get().simulate(delta_f);

    EntityManager::get().update_all_entities(delta_f);
}
