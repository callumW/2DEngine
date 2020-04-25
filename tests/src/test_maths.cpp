#include "game_math.h"

#include <cmath>
#include <iostream>
#include <limits>

static bool approx(float a, float b)
{
    float diff = std::abs(a - b);
    a = std::abs(a);
    b = std::abs(b);
    float largest = (b > a) ? b : a;
    return diff <= (largest * std::numeric_limits<float>::epsilon());
}


int main()
{
    // Test Clamp func
    // if (!approx(clamp_trig_arg(-2.2f), -0.2f)) {
    //     std::cout << "clamp_trig_arg failed " << __func__ << ":" << __LINE__ << " "
    //               << clamp_trig_arg(-2.2f) << std::endl;
    // }
    // if (!approx(clamp_trig_arg(-2.0f), 0.0f)) {
    //     std::cout << "clamp_trig_arg failed " << __func__ << ":" << __LINE__ << " "
    //               << clamp_trig_arg(-2.0f) << std::endl;
    // }
    // if (!approx(clamp_trig_arg(2.0f), 0.0f)) {
    //     std::cout << "clamp_trig_arg failed " << __func__ << ":" << __LINE__ << " "
    //               << clamp_trig_arg(2.0f) << std::endl;
    // }
    // if (!approx(clamp_trig_arg(2.9f), 0.9f)) {
    //     std::cout << "clamp_trig_arg failed " << __func__ << ":" << __LINE__ << " "
    //               << clamp_trig_arg(2.9f) << std::endl;
    // }

    vec2f_t x_axis{0.0f, 1.0f};
    vec2f_t y_axis{1.0f, 0.0f};

    std::cout << "x_axis: " << x_axis.angle() << std::endl;
    std::cout << "y_axis: " << y_axis.angle() << std::endl;
    std::cout << "y = x: " << vec2f_t{1.0f, 1.0f}.angle() << std::endl;

    if (!approx(y_axis.inner_angle(x_axis), 90.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << y_axis.inner_angle(x_axis) << std::endl;
    }

    vec2f_t neg_x(0.0f, -1.0f);
    if (!approx(neg_x.angle(), -90.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << neg_x.angle() << std::endl;
    }

    vec2f_t neg_y(-1.0f, 0.0f);
    if (!approx(neg_y.angle(), 180.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << neg_y.angle() << std::endl;
    }


    return 0;
}
