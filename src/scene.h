#pragma once

#include "entity.h"
#include "text.h"
#include "debug.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

class Scene {
public:
    using EntityList = std::vector<Entity>;
    using TextMap = std::map<std::string, Text>;

public:
    void add_entity(Entity&& entity);

    void add_text(const std::string& tag, Text&& text);

    void reset_text(const std::string& tag, const std::string& new_text);

    void update(float dt);

    const EntityList& entity_list() const;

    const TextMap& text_map() const;

private:
    EntityList _elist;
    TextMap _txtmap;
};

using ScenePtr = std::unique_ptr<Scene>;

inline
void Scene::add_entity(Entity&& entity)
{
    _elist.emplace_back(std::move(entity));
}

inline
void Scene::add_text(const std::string& tag, Text&& text)
{
    auto it = _txtmap.find(tag);
    if (it == _txtmap.end()) {
	_txtmap.emplace(tag, text);	
    }
}

inline
const Scene::EntityList& Scene::entity_list() const
{
    return _elist;
}

inline
const Scene::TextMap& Scene::text_map() const
{
    return _txtmap;
}

inline
void Scene::reset_text(const std::string& tag, const std::string& new_text)
{
    auto it = _txtmap.find(tag);
    if (_txtmap.find(tag) != _txtmap.end()) {
	it->second.set_text(new_text);
    }
}
