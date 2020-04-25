#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <ostream>

double const pi_d = 3.1415926;
double const pi_f = 3.1415926f;

inline double rad_to_degrees(double radians) { return radians * 180.0 / pi_d; }

inline float rad_to_degrees(float radians) { return radians * 180.0f / pi_f; }

inline double degress_to_radians(double degrees) { return degrees * pi_d / 180.0; }

inline float degress_to_radians(float degrees) { return degrees * pi_f / 180.0; }

inline float clamp_trig_arg(float arg)
{
    if (arg < -1.0f) {
        arg -= ceilf(arg);
    }
    else if (arg > 1.0f) {
        arg -= floorf(arg);
    }
    return arg;
}

typedef struct vec2f_t {
    float x;
    float y;

    vec2f_t& operator+=(vec2f_t const& other);
    vec2f_t& operator*=(float const scalar);
    vec2f_t& operator/=(float const scalar);

    vec2f_t(vec2f_t const& other);
    vec2f_t(float xx, float yy);
    vec2f_t(float xy);
    vec2f_t() : vec2f_t(0.0f){};

    float length() const;
    vec2f_t normalised() const;
    float dot(vec2f_t const& other) const;
    float inner_angle(vec2f_t const& other) const;
    float angle() const;

    vec2f_t get_rotated(float const& angle) const;

    static vec2f_t from_angle(float angle, float len = 1.0f);

} vec2f_t;

vec2f_t operator+(vec2f_t const& lhs, vec2f_t const& rhs);
vec2f_t operator-(vec2f_t const& lhs, vec2f_t const& rhs);
vec2f_t operator*(vec2f_t const& lhs, float const& rhs);
vec2f_t operator*(float const& lhs, vec2f_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, vec2f_t const& rhs);

typedef struct transform_t {
    vec2f_t position;
    float rotation;
} transform_t;
#endif
