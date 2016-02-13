#pragma once

#include "entity/abstractvisualentity.h"
#include "text/text.h"
#include "debug/debug.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

class IRenderer;

class Scene {
public:
    using EntityPtrList = std::vector<IVisualEntityPtr>;
    using TextMap = std::map<std::string, Text>;

public:
    void add_entity(IVisualEntityPtr&& entity);

    void add_text(const std::string& tag, Text&& text);

    void reset_text(const std::string& tag, const std::string& new_text);

    void update(float dt);

    void render_scene(IRenderer& render);

    const EntityPtrList& entity_list() const;

    const TextMap& text_map() const;

private:
    EntityPtrList _elist;
    TextMap _txtmap;
};

using ScenePtr = std::unique_ptr<Scene>;

inline
void Scene::add_entity(IVisualEntityPtr&& entity)
{
    _elist.emplace_back(IVisualEntityPtr{entity.release()});
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
const Scene::EntityPtrList& Scene::entity_list() const
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
