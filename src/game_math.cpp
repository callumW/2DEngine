#include "game_math.h"

#include <cmath>
#include <iostream>

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

float vec2f_t::length() const { return std::sqrt(x * x + y * y); }

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

vec2f_t operator/(vec2f_t const& lhs, float const& rhs) { return {(lhs.x / rhs), (lhs.y / rhs)}; }
vec2f_t operator/(float const& lhs, vec2f_t const& rhs) { return rhs / lhs; }

std::ostream& operator<<(std::ostream& lhs, vec2f_t const& rhs)
{
    lhs << "(" << rhs.x << "," << rhs.y << ")";
    return lhs;
}

vec2f_t vec2f_t::normalised() const
{
    float len = length();
    vec2f_t ret;
    if (len != 0) {
        if (x != 0) {
            ret.x = x / len;
        }
        if (y != 0) {
            ret.y = y / len;
        }
    }
    return ret;
}

float vec2f_t::dot(vec2f_t const& other) const { return x * other.x + y * other.y; }

float vec2f_t::angle() const
{
    // static vec2f_t const origin{0.0f, 0.0f};
    return rad_to_degrees(std::atan2(y, x));
}

float vec2f_t::inner_angle(vec2f_t const& other) const
{
    return rad_to_degrees(std::atan2(x * other.y - y * other.x, x * other.x + y * other.y));
}

vec2f_t vec2f_t::get_rotated(float const& angle) const
{
    float const rads = degress_to_radians(angle);
    return {x * std::cos(rads) - y * std::sin(rads), x * std::sin(rads) + y * std::cos(rads)};
}

vec2f_t vec2f_t::from_angle(float angle, float len)
{
    float rad = degress_to_radians(angle);
    return {len * std::cos(rad), len * std::sin(rad)};
}

std::ostream& operator<<(std::ostream& lhs, transform_t const& rhs)
{
    lhs << rhs.position << ", " << rhs.rotation << " degrees" << std::endl;
    return lhs;
}
