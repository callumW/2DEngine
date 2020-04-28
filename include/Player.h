#ifndef PLAYER_H
#define PLAYER_H
#include "Bullet.h"
#include "Entity.h"

float const PLAYER_ROT_OFFSET = -90.0f;

float const PLAYER_MOVEMENT_SPEED = 250.0f; // pixels per second
float const PLAYER_FIRE_RATE = 20.0f;
float const TIME_BETWEEN_FIRE = 1.0f / PLAYER_FIRE_RATE;

class Player : public Entity {
public:
    Player();

    virtual void update(float delta);
    virtual void render();


    void fire(vec2f_t const& direction, float impulse);

    std::vector<Bullet*> bullets;

    float time_since_last_fire = 0.0f;
};
#endif
