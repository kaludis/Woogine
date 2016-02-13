#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    _view_matrix = glm::lookAt(
    			       glm::vec3(0.0f, 0.0f, 0.0f),
    			       glm::vec3(0.0f, 0.0f, -1.0f),
    			       glm::vec3(0.0f, 1.0f, 0.0f)
    			       );
}

