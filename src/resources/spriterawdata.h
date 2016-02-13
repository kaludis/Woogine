#pragma once

#include "texturerawdata.h"

#include <vector>
#include <memory>

struct SpriteRawData {
    TextureRawData texture_data;
    unsigned int sprite_width;
    unsigned int sprite_height;
    unsigned int sprites_count;
    unsigned int sprites_stride;
    unsigned int sprites_rows;
};

using SpriteRawDataPtr = std::unique_ptr<SpriteRawData>;
