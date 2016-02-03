#pragma once

#include "resourcemanager.h"
#include "entity.h"

#include <string>
#include <memory>

class EntityCreator {
private:
    using ResourceManagerPtr = std::unique_ptr<ResourceManager>;

public:
    EntityCreator()
	: _presman{new ResourceManager{}}
    {}

    Entity create_entity(const std::string& entity_name);

    void set_entity_file(const std::string& entity_file);

private:
    void _entity_files();

private:
    ResourceManagerPtr _presman;

    std::string _entity_file;
    std::string _entity_name;

    std::string _vs_file;
    std::string _fs_file;
    std::string _mesh_data_file;
    std::string _texture_file;    
};

inline
void EntityCreator::set_entity_file(const std::string& entity_file)
{
    _entity_file = entity_file;
}
