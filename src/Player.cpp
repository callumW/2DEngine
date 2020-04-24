#include "Player.h"
#include "input.h"

#include <iostream>

Player::Player() : Entity("./assets/G.bmp", {0, 0, 40, 40}) {}

void Player::update(float delta)
{
    vec2f_t new_pos = world_pos;
    if (INPUT.KEY_W) {
        new_pos.y -= PLAYER_MOVEMENT_SPEED * delta;
    }
    else if (INPUT.KEY_S) {
        new_pos.y += PLAYER_MOVEMENT_SPEED * delta;
    }

    if (INPUT.KEY_A) {
        new_pos.x -= PLAYER_MOVEMENT_SPEED * delta;
    }
    else if (INPUT.KEY_D) {
        new_pos.x += PLAYER_MOVEMENT_SPEED * delta;
    }

    set_world_pos(new_pos);

    float mouse_x = static_cast<float>(INPUT.mouse_x);
    float mouse_y = static_cast<float>(INPUT.mouse_y);

    vec2f_t dir = {(mouse_x - world_pos.x), (mouse_y - world_pos.y)};

    float new_rot = rad_to_degrees(atan2((mouse_y - world_pos.y), (mouse_x - world_pos.x)));

    set_rotation(static_cast<double>(new_rot));

    for (auto& bullet : bullets) {
        bullet->update(delta);
    }

    time_since_last_fire += delta;

    if (INPUT.mouse_left_click) {
        if (time_since_last_fire > TIME_BETWEEN_FIRE) {
            fire(dir, 400.0f);
            time_since_last_fire = 0.0f;
        }
    }

    Entity::update(delta);
}

void Player::render()
{
    for (auto& bullet : bullets) {
        bullet->render();
    }
    Entity::render();
}

void Player::fire(vec2f_t const& direction, float impulse)
{
    Bullet* bullet = new Bullet();

    bullet->set_world_pos(world_pos);

    vec2f_t force = direction.normalised() * impulse;

    bullet->add_force(force);

    bullets.push_back(bullet);
}
