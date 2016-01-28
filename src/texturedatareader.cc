#include "texturedatareader.h"
#include "datareaderexception.h"

#include <cstring>

#include <SDL2/SDL_image.h>

TextureRawDataPtr
TextureDataReader::read_texture_data(const std::string& filename)
{
    if (!filename.size()) throw DataReaderException{"Empty file name"};

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) throw DataReaderException{"Could not load image from file '" +
			  filename + "'"};

    int texsize = surface->h * surface->pitch;
    std::vector<unsigned char> data(texsize);
    std::memcpy(data.data(), surface->pixels, texsize);

    TextureRawData* ptexraw = new TextureRawData{};
    ptexraw->data = data;
    ptexraw->width = surface->w;
    ptexraw->height = surface->h;

    SDL_FreeSurface(surface);
    
    return TextureRawDataPtr{ptexraw};
}
