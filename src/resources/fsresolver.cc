#include "fsresolver.h"
#include "../exceptions/fsresolverexception.h"

#include "../utils/utils.h"

#include <sstream>

FSResolver::ProgramFiles
FSResolver::program_files(const std::string& entity_type)
{
    if (_entity_type != entity_type) {
	_entity_type = entity_type;
	fill_data();
    }
    
    return _program_files;
}

std::string FSResolver::mesh_file(const std::string& entity_type)
{
    if (_entity_type != entity_type) {
	_entity_type = entity_type;
	fill_data();
    }

    return _mesh_file;
}

std::string FSResolver::texture_file(const std::string& entity_type)
{
    if (_entity_type != entity_type) {
	_entity_type = entity_type;
	fill_data();
    }

    return _texture_file;
}

void FSResolver::fill_data()
{
    std::ifstream ifs{_datafile};
    if (!ifs.is_open()) throw FSResolverException{"Could not open data file '" +
				_datafile + "'"};
    bool filled{false};
    std::string line{};
    while (std::getline(ifs, line)) {
	if (line.find(_entity_type) != std::string::npos) {
	    utils::strings::StringList slist =
		utils::strings::split(line, ";");
	    _program_files.vs_file = slist[1];
	    _program_files.fs_file = slist[2];
	    _mesh_file = slist[3];
	    _texture_file = slist[4];
	    filled = true;
	}
    }

    if (!filled) throw FSResolverException{"No data found for entity '" +
			 _entity_type + "'"};
    ifs.close();
}
