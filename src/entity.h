#pragma once

#include "entityresources.h"

#include <glm/glm.hpp>

#include <string>
#include <memory>

class EntityCreator;

class Entity {
public:
    friend EntityCreator;
    
    Entity()
	: _model_matrix(1.0f)
    {}

    const EntityResources& resources() const;

    const std::string& name() const;

private:
    std::string _name;
    EntityResources _res;

    glm::mat4 _model_matrix;
};

using EntityPtr = std::unique_ptr<Entity>;

inline
const EntityResources& Entity::resources() const
{
    return _res;
}

inline
const std::string& Entity::name() const
{
    return _name;
}