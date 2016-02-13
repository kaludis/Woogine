#pragma once

#include <memory>

#include <glm/glm.hpp>

class ICamera {
public:
    virtual const glm::mat4& view_matrix() const = 0;
};

using ICameraPtr = std::unique_ptr<ICamera>;
