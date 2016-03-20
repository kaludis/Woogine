#pragma once

#include <vector>
#include <memory>

struct TextureRawData {
    enum class TextureType {
	Simple,
	    Tiled
    };

    std::vector<unsigned char> data;
    unsigned int width;
    unsigned int height;
};

using TextureRawDataPtr = std::unique_ptr<TextureRawData>;
