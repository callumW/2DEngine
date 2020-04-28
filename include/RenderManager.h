#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "RenderComponent.h"

class RenderManager {
public:
    static RenderManager& get();

    void render_all();

    render_component_t* new_render_component();

private:
    RenderManager() = default;

    void render(render_component_t& comp);

    size_t first_free_render_component = 0;
    std::array<render_component_t, MAX_NUM_ENTITIES> render_components;
};
#endif
