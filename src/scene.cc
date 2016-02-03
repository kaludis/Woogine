#include "scene.h"

void Scene::update(float dt)
{
    for (Entity& entity : *_elist) {
	entity.update(dt);
    }
}
