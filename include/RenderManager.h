#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "ComponentManager.h"
#include "RenderComponent.h"

class RenderManager : public ComponentManager<render_component_t> {
public:
    static RenderManager& get();

    void render_all();

    render_component_t* create_render_component(entity_t* entity, std::string const& tex_path);

private:
    RenderManager() = default;
};
#endif
