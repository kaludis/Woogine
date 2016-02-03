#include "camera.h"

Camera::Camera()
{
    _view_matrix = glm::lookAt(
			       glm::vec3(0.0f, 2.0f, 0.0f),
			       glm::vec3(0.0f, 0.0f, -4.0f),
			       glm::vec3(0.0f, 1.0f, 0.0f)
			       );

    _projection_matrix = glm::perspective(
					  45.0f, 
					  1.0f * 1024 / 768,
					  0.1f, 
					  10.0f
					  );
}
