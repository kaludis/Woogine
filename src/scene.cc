#include "scene.h"
#include "entity/entity.h"
#include "renderer/abstractrenderer.h"

void Scene::update(float dt)
{
    for (const IVisualEntityPtr& entity : _elist) {
	entity->update(dt);
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
