#pragma once

#include "meshrawdata.h"

#include <string>
#include <vector>
#include <fstream>

class MeshDataReader {
public:
    MeshRawDataPtr read_mesh_data(const std::string& filename);

private:
    void read_data(const std::string& data_type, std::ifstream& ifs);

private:
    std::string _filename;

    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<float> _texuvcoords;
};
