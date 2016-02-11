#pragma once

#include "entityresources.h"

#include "debug.h"

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <chrono>

class EntityCreator;

class Entity {
public:
    friend EntityCreator;
    
    Entity(const std::string& name)
	: _name{name},
	_model_matrix(1.0f),
	_is_init{false}
    {}

    void update(float dt);

    const EntityResources& resources() const;

    std::string name() const;

    std::string model() const;    

    const glm::mat4& model_matrix() const;

private:
    std::string _name;
    std::string _model;
    EntityResources _res;
    glm::mat4 _model_matrix;
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
std::string Entity::model() const
{
    return _model;
}

inline
const glm::mat4& Entity::model_matrix() const
{
    return _model_matrix;
}
