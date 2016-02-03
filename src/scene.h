#pragma once

#include "entity.h"
#include "debug.h"

#include <vector>
#include <memory>

class Scene {
public:
    using EntityList = std::vector<Entity>;
    using EntityListPtr = std::unique_ptr<EntityList>;

public:
    Scene()
	: _elist{new EntityList{}}
    {}
    
    void add_entity(Entity&& entity);

    void update(float dt);

    const EntityListPtr& entity_list() const;

private:
    EntityListPtr _elist;
};

using ScenePtr = std::unique_ptr<Scene>;

inline
void Scene::add_entity(Entity&& entity)
{
    _elist->emplace_back(std::move(entity));
}

inline
const Scene::EntityListPtr& Scene::entity_list() const
{
    return _elist;
}
