#include "entitycreator.h"
#include "entitycreatorexc.h"
#include "utils.h"

#include "sprite.h"
#include "debug.h"

#include <fstream>

Entity
EntityCreator::create_entity(const std::string& entity_name, const std::string& entity_model)
{
    if(_entity_model != entity_model) {
	_entity_model = entity_model;	
	_entity_files();
    }

    Entity entity{entity_name};
    entity._res.program = _presman->entity_program(_vs_file, _fs_file);
    entity._res.mesh = _presman->entity_mesh(_data_file);
    entity._res.texture = _presman->entity_texture(_texture_file);
    entity._res.sprite = _presman->entity_sprite(_sprite_file);

    return entity;
}

Text EntityCreator::create_text(const std::string& entity_model,
				const std::string& text, const Point2f& position,
				float scale, const glm::vec3& color)
{
    if(_entity_model != entity_model) {
	_entity_model = entity_model;	
	_entity_files();
    }

    Text txt{text, position, scale, color};
    txt._program = _presman->text_program(_vs_file, _fs_file);
    txt._mesh = _presman->text_mesh(txt.program());

    return txt;
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
	std::string::size_type pos = line.find(_entity_model);
	if ((pos != std::string::npos) && (line[pos + _entity_model.length()] == ';')) {
	    utils::strings::StringList slist =
		utils::strings::split(line, ";");
	    _vs_file = slist[1];
	    _fs_file = slist[2];
	    _data_file = slist[3];
	    _texture_file = slist[4];
	    _sprite_file = slist[5];
	    filled = true;
	}
    }

    if (!filled) throw EntityCreatorException{"No data found for entity '" +
			 _entity_model + "'"};    

    ifs.close();    
}
