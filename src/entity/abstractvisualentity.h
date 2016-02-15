#pragma once

#include "abstractentity.h"

#include <string>
#include <memory>

#include <glm/glm.hpp>

class IRenderer;
class IController;

struct EntityResources;

class IVisualEntity : public IEntity {
public:
    virtual void accept_renderer(IRenderer& renderer) = 0;

    virtual void accept_controller(IController& controller) = 0;    

    virtual std::string asset_name() const = 0;

    virtual const EntityResources& resources() const = 0;

    virtual const glm::mat4& model_matrix() const = 0;
};

using IVisualEntityPtr = std::unique_ptr<IVisualEntity>;
