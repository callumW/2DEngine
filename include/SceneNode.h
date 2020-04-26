#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <memory>
#include <vector>

#include "game_math.h"

class SceneNode {
public:
    ~SceneNode();

    /**
     * Change position local to parent
     */
    virtual void set_local_transform(transform_t const& transform);

    /**
     * Change position in world space (irrelevant of parent position)
     */
    virtual void set_world_transform(transform_t const& transform);

    virtual void render();

    virtual void update(float delta);

    virtual void add_child(std::weak_ptr<SceneNode> child);

    virtual void remove_child(SceneNode* child);

    virtual void remove_from_parent();

    virtual void set_hidden(bool hide = true) { is_hidden = hide; }

    bool hidden() const { return is_hidden; }

protected:
    virtual void recalc_local_transform();
    virtual void recalc_world_transform();

    void update_children_world_transforms();


    transform_t local_transform;
    transform_t world_transform;

    bool is_hidden = false;

    std::vector<std::weak_ptr<SceneNode>> children;
    SceneNode* parent = nullptr;
};

extern SceneNode root_node;
#endif
