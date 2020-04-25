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

    vec2f_t x_axis{0.0f, 99999.0f};
    vec2f_t y_axis{99999.0f, 0.0f};

    if (!approx(x_axis.angle(y_axis), 90.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << x_axis.angle(y_axis) << std::endl;
    }

    vec2f_t neg_x(0.0f, -9999.0f);
    if (!approx(neg_x.angle(), 180.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << neg_x.angle() << std::endl;
    }

    vec2f_t neg_y(-9999.0f, 0.0f);
    if (!approx(neg_y.angle(), -90.0f)) {
        std::cout << "angle failed " << __func__ << ":" << __LINE__ << " "
                  << neg_y.angle() << std::endl;
    }


    return 0;
}
