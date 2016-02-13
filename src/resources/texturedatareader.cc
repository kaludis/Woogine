#include "texturedatareader.h"
#include "../exceptions/datareaderexception.h"
#include "imageloader.h"

#include <cstring>

TextureRawDataPtr
TextureDataReader::read_texture_data(const std::string& filename)
{
    if (!filename.size()) throw DataReaderException{"Empty file name"};

    ImageLoader image_loader{};
    ImageLoader::ImageData image_data = image_loader.read_data(filename);

    TextureRawData* ptexraw = new TextureRawData{};
    ptexraw->data = image_data.data;
    ptexraw->width = image_data.width;
    ptexraw->height = image_data.height;
    
    return TextureRawDataPtr{ptexraw};
}
