#include "entitycreator.h"
#include "entitycreatorexc.h"
#include "utils.h"

#include <fstream>

EntityPtr
EntityCreator::create_entity(const std::string& entity_name)
{
    if (!entity_name.size()) {
	throw EntityCreatorException{"Empty entity name"};
    }

    if(_entity_name != entity_name) {
	_entity_name = entity_name;	
	_entity_files();
    }

    // DEBUG_PRINT("files:\n%s\n%s\n%s\n%s\n",
    // 		_vs_file.c_str(),
    // 		_fs_file.c_str(),
    // 		_mesh_data_file.c_str(),
    // 		_texture_file.c_str());
    
    EntityResources res;
    res.program = _presman->entity_program(_vs_file, _fs_file);
    res.mesh = _presman->entity_mesh(_mesh_data_file);
    res.texture = _presman->entity_texture(_texture_file);

    Entity* entity = new Entity;
    entity->_res = res;
    entity->_name = _entity_name;

    return EntityPtr{entity};
}

void EntityCreator::_entity_files()
{
    std::ifstream ifs{_entity_file};
    if (!ifs.is_open()) {
	throw EntityCreatorException{"Entity data file '" +
		_entity_file + "' does not exists"};
    }

    bool filled{false};
    std::string line{};
    while (std::getline(ifs, line)) {
	std::string::size_type pos = line.find(_entity_name);
	if ((pos != std::string::npos) && (line[pos + _entity_name.length()] == ';')) {
	    utils::strings::StringList slist =
		utils::strings::split(line, ";");
	    _vs_file = slist[1];
	    _fs_file = slist[2];
	    _mesh_data_file = slist[3];
	    _texture_file = slist[4];
	    
	    filled = true;
	}
    }

    if (!filled) throw EntityCreatorException{"No data found for entity '" +
			 _entity_name + "'"};    

    ifs.close();    
}