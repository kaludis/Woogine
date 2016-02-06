#include "entity.h"

#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <cmath>
#include <chrono>

constexpr unsigned int msec_per_sec = 1000000;

void Entity::update(float dt)
{
    static bool first_sprite{true};
    if (first_sprite) {
	_res.sprite.next();
	first_sprite = false;
    }
    // float time_passed = SDL_GetTicks() / 1000.0f;

    // glm::mat4 model = glm::mat4(1.0f);

    // glm::vec3 axis_z(0.0f, 0.0f, 1.0f);

    // float scale_factor = std::abs(std::sin(time_passed));

    // glm::mat4 anim = glm::scale(glm::vec3(scale_factor, scale_factor, 0.0f));

    // _model_matrix = model * anim;
    
    std::chrono::system_clock::time_point now =
	std::chrono::system_clock::now();    
    static std::chrono::system_clock::time_point prev = now;

    

    if (std::chrono::duration_cast<std::chrono::microseconds>
	(now - prev).count() >= msec_per_sec / 20) {
	prev = now;
	_res.sprite.next();
    }
}
