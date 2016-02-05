#include "entity.h"

#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <cmath>

void Entity::update(float dt)
{
    float time_passed = SDL_GetTicks() / 1000.0f;

    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 axis_z(0.0f, 0.0f, 1.0f);

    float scale_factor = std::abs(std::sin(time_passed));

    glm::mat4 anim = glm::scale(glm::vec3(scale_factor, scale_factor, 0.0f));

    _model_matrix = model * anim;
}
