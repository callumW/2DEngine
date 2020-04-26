#include "SceneNode.h"

SceneNode root_node;

void SceneNode::set_local_transform(transform_t const& transform)
{
    local_transform = transform;
    recalc_world_transform();
}

void SceneNode::set_world_transform(transform_t const& transform)
{
    world_transform = transform;
    recalc_local_transform();
}

void SceneNode::render()
{
    if (!is_hidden) {
        for (auto& child : children) {
            child->render();
        }
    }
}

void SceneNode::update(float delta)
{
    update_children_world_transforms();
    for (auto it = children.begin(); it != children.end();) {
        if ((*it)->alive()) {
            (*it)->update(delta);
            it++;
        }
        else {
            delete *it;
            it = children.erase(it);
        }
    }
}

void SceneNode::add_child(SceneNode* child)
{
    if (child) {
        child->remove_from_parent();

        children.push_back(child);
        child->parent = this;
        child->recalc_world_transform();
    }
}

void SceneNode::remove_child(SceneNode* child)
{
    if (child) {
        auto end = children.end();
        for (auto it = children.begin(); it != end; it++) {
            if ((*it) == child) {
                children.erase(it);
                return;
            }
        }
    }
}

void SceneNode::remove_from_parent()
{
    if (parent != nullptr) {
        parent->remove_child(this);
        parent = nullptr;
    }
}

void SceneNode::recalc_local_transform()
{
    if (parent != nullptr) {
        local_transform.position = world_transform.position - parent->world_transform.position;
    }
    else {
        local_transform = world_transform;
    }
    update_children_world_transforms();
}

void SceneNode::recalc_world_transform()
{
    if (parent != nullptr) {
        world_transform.position =
            parent->world_transform.position +
            local_transform.position.get_rotated(parent->local_transform.rotation);
        world_transform.rotation = local_transform.rotation + parent->world_transform.rotation;
    }
    else {
        world_transform = local_transform;
    }
    update_children_world_transforms();
}

SceneNode::~SceneNode()
{
    for (auto& child : children) {
        delete child;
    }
}

void SceneNode::update_children_world_transforms()
{
    for (auto& child : children) {
        child->recalc_world_transform();
    }
}
