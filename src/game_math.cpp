#include "game_math.h"

#include <cmath>

vec2f_t& vec2f_t::operator+=(vec2f_t const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

vec2f_t& vec2f_t::operator*=(float const scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

vec2f_t& vec2f_t::operator/=(float const scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}


vec2f_t::vec2f_t(vec2f_t const& other)
{
    x = other.x;
    y = other.y;
}

vec2f_t::vec2f_t(float xx, float yy)
{
    x = xx;
    y = yy;
}

vec2f_t::vec2f_t(float xy)
{
    x = xy;
    y = xy;
}

float vec2f_t::length() { return std::sqrt(x * x + y * y); }

vec2f_t operator+(vec2f_t const& lhs, vec2f_t const& rhs)
{
    return {(lhs.x + rhs.x), (lhs.y + rhs.y)};
}

vec2f_t operator-(vec2f_t const& lhs, vec2f_t const& rhs)
{
    return {(lhs.x - rhs.x), (lhs.y - rhs.y)};
}

vec2f_t operator*(vec2f_t const& lhs, float const& rhs) { return {(lhs.x * rhs), (lhs.y * rhs)}; }

vec2f_t operator*(float const& lhs, vec2f_t const& rhs) { return rhs * lhs; }

std::ostream& operator<<(std::ostream& lhs, vec2f_t const& rhs)
{
    lhs << "(" << rhs.x << "," << rhs.y << ")";
    return lhs;
}
