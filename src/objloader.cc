#include "objloader.h"

#include <string>
#include <sstream>

#include <iostream>

using std::cout;
using std::endl;

ObjDataPtr ObjLoader::read_data(const std::string& filename)
{
    std::ifstream ifs{filename};
    if (!ifs.is_open()) {
	_error = ObjLoaderError::FileNotExists;
	return ObjDataPtr{nullptr};
    }

    ObjData* objdata = new ObjData;
    objdata->vertices =
	_read_attributes<ObjData::VerticesArray>("v", ifs);
    objdata->normals =
	_read_attributes<ObjData::NormalsArray>("vn", ifs);
    objdata->indices =
	_read_attributes<ObjData::IndicesArray>("f", ifs);

    if (!objdata->vertices.size() ||
	!objdata->normals.size() || !objdata->indices.size()) {
	_error = ObjLoader::ObjLoaderError::BadFileFormat;
	return ObjDataPtr{nullptr};
    }

    return ObjDataPtr{objdata};
}

template <typename T>
T ObjLoader::_read_attributes(const std::string& attr_type, std::ifstream& ifs)
{
    std::string type = attr_type + " ";

    T attr_array{};
    std::string line{};

    bool in_block{false};
    while (std::getline(ifs, line)) {
	std::string::size_type pos = line.find(type);
	if (pos != std::string::npos) {
	    in_block = true;
	    typename T::value_type data;
	    std::stringstream ss{line.substr(attr_type.length() + 1,
					     line.length() - attr_type.length())};
	    while (ss >> data) {
		attr_array.push_back(data);
	    }
	} else if (in_block) {
	    break;
	}
    }

    return attr_array;
}
