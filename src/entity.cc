#include "entity.h"

#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void Entity::update(float dt)
{
    float time_passed = SDL_GetTicks() / 1000.0f;

    glm::mat4 model = glm::translate(
				   glm::mat4(1.0f),
				   glm::vec3(0.0f, -1.0f, -6.0f));

    glm::vec3 axis_y(0.0f, 1.0f, 0.0f);

    glm::mat4 anim = glm::rotate(
				 glm::mat4(1.0f),
				 glm::radians(time_passed * 45.0f * dt),
				 axis_y
				 );

    _model_matrix = model * anim;
}
