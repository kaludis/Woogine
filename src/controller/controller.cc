#include "controller.h"
#include "../entity/entity.h"
#include "../math/point.hpp"
#include "../input/keys.h"
#include "../input/input.h"
#include "../debug/debug.h"

void Controller::process(Entity& entity)
{
    Point2f pos = entity.position();
    float velocity  = entity.velocity() * _dt;

    if (_pinput->keystate("kUp")) {
	entity.set_position(Point2f{pos.xpos(), pos.ypos() + velocity});
	DEBUG_MSG("Up\n");
    }

    if (_pinput->keystate("kDown")) {
	entity.set_position(Point2f{pos.xpos(), pos.ypos() - velocity});
	DEBUG_MSG("Down\n");	
    }

    if (_pinput->keystate("kLeft")) {
	entity.set_position(Point2f{pos.xpos() - velocity, pos.ypos()});
	DEBUG_MSG("Left\n");	
    }

    if (_pinput->keystate("kRight")) {
	entity.set_position(Point2f{pos.xpos() + velocity, pos.ypos()});
	DEBUG_MSG("Right\n");	
    }
}
