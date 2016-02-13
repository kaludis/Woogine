#include "spritedatareader.h"
#include "../resources/imageloader.h"
#include "../utils/utils.h"
#include "../debug/debug.h"

#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

SpriteRawDataPtr
SpriteDataReader::read_sprite_data(const std::string& filename)
{
    using namespace utils::strings;

    std::ifstream ifs{filename};
    if (!ifs.is_open()) {
	DEBUG_PRINT("No such file '%s'\n", filename.c_str());
	return SpriteRawDataPtr{nullptr};
    }

    SpriteRawData* sdata = new SpriteRawData;

    std::string sfile;
    std::string line;
    while (std::getline(ifs, line)) {
	if (line.find("file") != std::string::npos) {
	    sfile = split(line, " ")[1];
	}

	if (line.find("swidth") != std::string::npos) {
	    std::stringstream ss{split(line, " ")[1]};
	    ss >> sdata->sprite_width;
	}

	if (line.find("sheight") != std::string::npos) {
	    std::stringstream ss{split(line, " ")[1]};
	    ss >> sdata->sprite_height;
	}

	if (line.find("scount") != std::string::npos) {
	    std::stringstream ss{split(line, " ")[1]};
	    ss >> sdata->sprites_count;
	}

	if (line.find("sstride") != std::string::npos) {
	    std::stringstream ss{split(line, " ")[1]};
	    ss >> sdata->sprites_stride;
	}

	if (line.find("srows") != std::string::npos) {
	    std::stringstream ss{split(line, " ")[1]};
	    ss >> sdata->sprites_rows;
	}	
    }

    ImageLoader image_loader{};
    ImageLoader::ImageData image_data = image_loader.read_data(sfile);

    sdata->texture_data.data = image_data.data;
    sdata->texture_data.width = image_data.width;
    sdata->texture_data.height = image_data.height;

    return SpriteRawDataPtr{sdata};
}
