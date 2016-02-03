#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

class Camera {
public:
    Camera();

    const glm::mat4& projection_matrix() const;

    const glm::mat4& view_matrix() const;

private:
    glm::mat4 _projection_matrix;
    glm::mat4 _view_matrix;
};

using CameraPtr = std::unique_ptr<Camera>;

inline
const glm::mat4& Camera::projection_matrix() const
{
    return _projection_matrix;
}

inline
const glm::mat4& Camera::view_matrix() const
{
    return _view_matrix;
}
