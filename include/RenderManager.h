#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "ComponentManager.h"
#include "RenderComponent.h"

class RenderManager : public ComponentManager<render_component_t> {
public:
    RenderManager();
    void render_all();

private:
    void render(render_component_t& comp);
};
#endif
