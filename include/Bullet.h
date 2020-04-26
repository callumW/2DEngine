#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

float const BULLET_LIFE_SPAN = 0.5f;

class Bullet : public Entity {
public:
    Bullet();

    virtual void update(float delta);

    bool alive() const { return is_alive; }

private:
    float age = 0.0f;
    bool is_alive = true;
};
#endif
