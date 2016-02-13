#pragma once

#include "resources/resourcemanager.h"
#include "entity/entity.h"
#include "entity/abstractvisualentity.h"
#include "text/text.h"
#include "math/point.hpp"

#include <string>
#include <memory>

class EntityCreator {
private:
    using ResourceManagerPtr = std::unique_ptr<ResourceManager>;

public:
    EntityCreator()
	: _presman{new ResourceManager{}}
    {}

    IVisualEntityPtr create_entity(const std::string& entity_name,
			 const std::string& entity_model);

    Text create_text(const std::string& entity_name,
		     const std::string& text, const Point2f& position,
		     float scale = 1.0f, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

    void set_entities_file(const std::string& entity_file);

private:
    void _entity_files();

private:
    ResourceManagerPtr _presman;

    std::string _entity_file;
    std::string _entity_model;

    std::string _vs_file;
    std::string _fs_file;
    std::string _data_file;
    std::string _texture_file;
    std::string _sprite_file;
};

inline
void EntityCreator::set_entities_file(const std::string& entity_file)
{
    _entity_file = entity_file;
}
