#include "meshdatareader.h"
#include "../exceptions/datareaderexception.h"

#include "../debug/debug.h"

#include <iostream>
#include <sstream>
#include <string>

MeshRawDataPtr MeshDataReader::read_mesh_data(const std::string& filename)
{
    if (!filename.size()) throw DataReaderException{"Empty file name"};

    _filename = filename;

    std::ifstream ifs{_filename};

    if (!ifs.is_open()) throw DataReaderException{"File '" +
				_filename +
				"' does not exists"};
    read_data("vertices", ifs);
    read_data("indices", ifs);
    read_data("texuvcoords", ifs);

    ifs.close();

    if (!_vertices.size() || !_indices.size() || !_texuvcoords.size()) {
	throw DataReaderException{"Data file '" +
		_filename +
		"' has bad format or corrupted"};
    }

    MeshRawData* pmeshdata = new MeshRawData{};
    pmeshdata->vertices = _vertices;
    pmeshdata->indices = _indices;
    pmeshdata->texuvcoords = _texuvcoords;

    _vertices.clear();
    _indices.clear();
    _texuvcoords.clear();

    return MeshRawDataPtr{pmeshdata};
}

void MeshDataReader::read_data(const std::string& data_type, std::ifstream& ifs)
{
    bool out_of_section{false};
    std::string line{};
    while (std::getline(ifs, line) && !out_of_section) {
	if ((line[0] == '#') && (line.find(data_type) != std::string::npos)) {
	    while (std::getline(ifs, line)) {
		if (!line.size() || (line[0] == '#')) {
		    out_of_section = true;
		    break;
		}

		float value{0.0f};
		std::stringstream ss{line};
		while (ss >> value) {
		    if (data_type == "vertices") {
			_vertices.push_back(value);
		    } else if (data_type == "indices") {
			_indices.push_back(static_cast<unsigned short>(value));
		    } else if (data_type == "texuvcoords") {
			_texuvcoords.push_back(value);
		    }

		    if (ss.peek() == ' ') ss.ignore();
		}
	    }
	    break;
	}
    }    
}
