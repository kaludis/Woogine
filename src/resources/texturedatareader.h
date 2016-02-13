#pragma once

#include "texturerawdata.h"

#include <string>

class TextureDataReader {
public:
    TextureRawDataPtr read_texture_data(const std::string& filename);
};
