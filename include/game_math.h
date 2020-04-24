#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

double const pi_d = 3.1415926;
double const pi_f = 3.1415926f;

inline double rad_to_degrees(double radians) { return radians * 180.0 / pi_d; }

inline float rad_to_degrees(float radians) { return radians * 180.0f / pi_f; }

typedef struct vec2f_t {
    float x;
    float y;
} vec2f_t;

#endif
