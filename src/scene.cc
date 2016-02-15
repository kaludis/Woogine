#include "scene.h"
#include "entity/entity.h"
#include "renderer/abstractrenderer.h"
#include "controller/abstractcontroller.h"

void Scene::update(float dt, IController& controller)
{
    controller.set_dt(dt);
    
    for (const IVisualEntityPtr& entity : _elist) {
	entity->accept_controller(controller);
    }
}

void Scene::render_scene(IRenderer& render)
{
    for (const IVisualEntityPtr& entity : _elist) {
	entity->accept_renderer(render);
    }

    for (const auto& pair : _txtmap) {
	if (pair.second.text().length()) {
	    render.render_text(pair.second);
	}
    }
}
