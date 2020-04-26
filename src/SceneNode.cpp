#include "SceneNode.h"


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
            auto child_ptr = child.lock();
            if (child_ptr) {
                child_ptr->render();
            }
        }
    }
}

void SceneNode::update(float delta)
{
    update_children_world_transforms();
    for (auto& child : children) {
        auto child_ptr = child.lock();
        if (child_ptr) {
            child_ptr->update(delta);
        }
    }
}

void SceneNode::add_child(std::weak_ptr<SceneNode> child)
{
    std::shared_ptr<SceneNode> child_ptr = child.lock();
    if (child_ptr) {
        child_ptr->remove_from_parent();

        children.push_back(child_ptr);
        child_ptr->parent = this;
        child_ptr->recalc_world_transform();
    }
}

void SceneNode::remove_child(SceneNode* child)
{
    if (child) {
        auto end = children.end();
        for (auto it = children.begin(); it != end; it++) {
            auto tmp = (*it).lock();
            if (tmp) {
                if (tmp.get() == child) {
                    children.erase(it);
                    return;
                }
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
        auto child_ptr = child.lock();
        if (child_ptr) {
            child_ptr->parent = nullptr;
        }
    }
}

void SceneNode::update_children_world_transforms()
{
    for (auto& child : children) {
        auto child_ptr = child.lock();
        if (child_ptr) {
            child_ptr->recalc_world_transform();
        }
    }
}
