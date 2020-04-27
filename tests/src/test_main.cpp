#include "EntityManager.h"
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
    int failed_tests = 0;
    vec2f_t x_axis{0.0f, 1.0f};
    vec2f_t y_axis{1.0f, 0.0f};

    std::cout << "x_axis: " << x_axis.angle() << std::endl;
    std::cout << "y_axis: " << y_axis.angle() << std::endl;
    std::cout << "y = x: " << vec2f_t{1.0f, 1.0f}.angle() << std::endl;

    if (!approx(y_axis.inner_angle(x_axis), 90.0f)) {
        std::cout << "angle failed " << __FILE__ << ":" << __LINE__ << " "
                  << y_axis.inner_angle(x_axis) << std::endl;
        failed_tests++;
    }

    vec2f_t neg_x(0.0f, -1.0f);
    if (!approx(neg_x.angle(), -90.0f)) {
        std::cout << "angle failed " << __FILE__ << ":" << __LINE__ << " " << neg_x.angle()
                  << std::endl;
        failed_tests++;
    }

    vec2f_t neg_y(-1.0f, 0.0f);
    if (!approx(neg_y.angle(), 180.0f)) {
        std::cout << "angle failed " << __FILE__ << ":" << __LINE__ << " " << neg_y.angle()
                  << std::endl;
        failed_tests++;
    }

    entity_id_t entity_id;

    if (entity_id.generation() != 0 || entity_id.index() != 0) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << " | " << entity_id.index() << std::endl;
        failed_tests++;
    }

    entity_id.increment_generation();
    if (entity_id.generation() != 1) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << std::endl;
        failed_tests++;
    }


    entity_id.set_index(890);
    if (entity_id.generation() != 1 || entity_id.index() != 890) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << " | " << entity_id.index() << std::endl;
        failed_tests++;
    }

    entity_id.set_generation(1023);
    if (entity_id.generation() != 1023 || entity_id.index() != 890) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << " | " << entity_id.index() << std::endl;
        failed_tests++;
    }

    entity_id.increment_generation();
    if (entity_id.generation() != 0 || entity_id.index() != 890) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << " | " << entity_id.index() << std::endl;
        failed_tests++;
    }

    entity_id.set_generation(1022);
    entity_id.increment_generation();
    if (entity_id.generation() != 1023 || entity_id.index() != 890) {
        std::cout << "entity_id_t failed " << __FILE__ << ":" << __LINE__ << " "
                  << entity_id.generation() << " | " << entity_id.index() << std::endl;
        failed_tests++;
    }

    return failed_tests;
}
