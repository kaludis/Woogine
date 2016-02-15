#pragma once

#include "abstractvisualentity.h"
#include "../resources/entityresources.h"
#include "../debug/debug.h"
#include "../math/point.hpp"

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <chrono>

class IRenderer;
class IController;

class EntityCreator;

class Entity : public IVisualEntity {
public:
    friend EntityCreator;
    
    Entity(const std::string& name)
	: _name{name},
	_model{std::string{}},
	_model_matrix(1.0f),
	_position{Point2f{}},
	_velocity{0.1f},
	_is_init{false}
    {}

    //    void update(float dt) override;

    void accept_controller(IController& controller) override;    

    void accept_renderer(IRenderer& renderer) override;

    const EntityResources& resources() const override;

    std::string name() const override;

    std::string asset_name() const override;

    const glm::mat4& model_matrix() const override;

    void init() override;

    void set_position(const Point2f& position);
    
    Point2f position() const;

    void set_velocity(float velocity);

    float velocity() const;

private:
    std::string _name;
    std::string _model;
    EntityResources _res;
    glm::mat4 _model_matrix;
    Point2f _position;
    float _velocity;
    
    bool _is_init;
    std::chrono::system_clock::time_point _last_update;
};

using EntityPtr = std::unique_ptr<Entity>;

inline
const EntityResources& Entity::resources() const
{
    return _res;
}

inline
std::string Entity::name() const
{
    return _name;
}

inline
std::string Entity::asset_name() const
{
    return _model;
}

inline
const glm::mat4& Entity::model_matrix() const
{
    return _model_matrix;
}

inline
void Entity::init()
{
    _res.sprite.reset();    
}

inline
void Entity::set_position(const Point2f& position)
{
    _position = position;
}

inline
Point2f Entity::position() const
{
    return _position;
}

inline
void Entity::set_velocity(float velocity)
{
    _velocity = velocity;
}

inline
float Entity::velocity() const
{
    return _velocity;
}
