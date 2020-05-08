#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <array>

#include "ComponentManager.h"
#include "RenderComponent.h"

class RenderManager : public ComponentManager<render_component_t> {
public:
    static RenderManager& get();

    void render_all();

    virtual render_component_t* create_component(entity_t* entity) override;

private:
    RenderManager() = default;
};
#endif
