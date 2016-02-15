#include "entity.h"
#include "../renderer/abstractrenderer.h"
#include "../controller/abstractcontroller.h"
/*
#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
*/
//#include <cmath>

//constexpr unsigned int msec_per_sec = 1000000;
/*
void Entity::update(float dt)
{
    std::chrono::system_clock::time_point now =
	std::chrono::system_clock::now();    

    if (!_is_init) {
	_is_init = true;	
	//DEBUG_PRINT("Init sprite state for %s\n", _name.c_str());
	_res.sprite.reset();
	_last_update = now;	
    }

    //float time_passed = SDL_GetTicks() / 1000.0f;

    // glm::mat4 model = glm::mat4(1.0f);

    // glm::vec3 axis_z(0.0f, 0.0f, 1.0f);

    // float scale_factor = std::abs(std::sin(time_passed));

    // glm::mat4 anim = glm::scale(glm::vec3(scale_factor, scale_factor, 0.0f));

    // _model_matrix = model * anim;

    int velocity = 0;
    
    if (_name == "object1") {
	glm::mat4 model = glm::translate(glm::mat4(1.0f),
				      glm::vec3(-0.5f, 0.2f, 0.0f));
	_model_matrix = model;
	velocity = 20;
    }

    if (_name == "runmen") {
	velocity = 35;
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f),
				      glm::vec3(0.5f, 0.0f, 0.0f));

	glm::mat4 scale = glm::scale(glm::vec3(0.6f, 0.6f, 0.0f));

	_model_matrix = model * scale;
    }    

    if (std::chrono::duration_cast<std::chrono::microseconds>
	(now - _last_update).count() >= msec_per_sec / velocity * dt) {
	_last_update = now;
	_res.sprite.next();
    }
}
*/
void Entity::accept_controller(IController& controller)
{
    controller.process(*this);
}

void Entity::accept_renderer(IRenderer& renderer)
{
    renderer.render(*this);
}

