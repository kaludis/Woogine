#pragma once

#include <vector>
#include <memory>

struct MeshRawData {
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
    std::vector<float> texuvcoords;
};

using MeshRawDataPtr = std::unique_ptr<MeshRawData>;
