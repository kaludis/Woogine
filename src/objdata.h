#pragma once

#include <vector>
#include <memory>

struct ObjData {
    using VerticesArray = std::vector<float>;
    using NormalsArray = std::vector<float>;
    using IndicesArray = std::vector<unsigned short>;

    VerticesArray vertices;
    NormalsArray normals;
    IndicesArray indices;
};

using ObjDataPtr = std::unique_ptr<ObjData>;
