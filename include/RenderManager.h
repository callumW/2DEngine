#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "RenderComponent.h"

class RenderManager {
public:
    static RenderManager& get();

    void render_all();

    render_component_t* new_render_component();

    void check_for_dead_entities();

private:
    RenderManager();

    void render(render_component_t& comp);

    void update_dirty_positions();

    size_t first_free_render_component = 0;
    std::vector<render_component_t> render_components;
};
#endif
