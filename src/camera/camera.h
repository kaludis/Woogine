#pragma once

#include "abstractcamera.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <memory>

class Camera : public ICamera {
public:
    Camera();

    const glm::mat4& view_matrix() const override;

private:
    glm::mat4 _view_matrix;
};

using CameraPtr = std::unique_ptr<Camera>;

inline
const glm::mat4& Camera::view_matrix() const
{
    return _view_matrix;
}
