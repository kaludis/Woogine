#pragma once

#include "spriterawdata.h"

#include <string>

class SpriteDataReader {
public:
    SpriteRawDataPtr read_sprite_data(const std::string& filename);
};
