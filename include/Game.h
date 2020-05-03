#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <array>

#include "Entity.h"
#include "game_math.h"

class Game {
public:
    Game();
    ~Game();

    void render();

    void update(Uint32 delta);

    void cleanup();

    void update_player(float delta);
    entity_id_t m_player_id;

private:
    void fire_bullet(vec2f_t const& loc, vec2f_t const& force);

    void spawn_ball(vec2f_t const& loc);
};
#endif
