#ifndef GAME_H
#define GAME_H
#include <array>

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

#include "ContactListener.h"
#include "Entity.h"
#include "game_math.h"


class Game {
public:
    Game();
    ~Game() = default;

    void render();

    void update(Uint32 delta);

    void set_player_landed() { player_airborne = false; }

private:
    void spawn_ball(vec2f_t const& position);
    void spawn_player(vec2f_t const& position);

    void update_player(float const delta);

    void load_map();

    b2Vec2 gravity = {0.0f, -10.0f};
    entity_t* player = nullptr;
    ContactListener contact_listener;
    bool player_airborne = false;
};
#endif
