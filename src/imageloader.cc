#include "imageloader.h"
#include "../src/debug.h"

#include <fstream>
#include <algorithm>

ImageLoader::ImageData
ImageLoader::read_data(const std::string& filename)
{
    ImageData png_data{};
    
    if (filename.size()) _filename = filename;

    std::FILE* file = std::fopen(_filename.c_str(), "r");
    if (!file) {
	_error = ImageLoaderError::FileNotExists;
	return png_data;
    }

    _pfile.reset(file);
    
    if (!_check_format()) {
	_error = ImageLoaderError::BadFileFormat;
	return png_data;		
    }

    png_structp png_ptr =
	png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr) {
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr) {
	    png_init_io(png_ptr, _pfile.get());
	    png_set_sig_bytes(png_ptr, 8);
	    png_read_info(png_ptr, info_ptr);

	    png_data.width = png_get_image_width(png_ptr, info_ptr);
	    png_data.height = png_get_image_height(png_ptr, info_ptr);
	    png_data.stride = png_get_rowbytes(png_ptr, info_ptr);
	    png_data.color_type = png_get_color_type(png_ptr, info_ptr);
	    png_data.bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	    png_read_update_info(png_ptr, info_ptr);

	    unsigned char** raw_data = new unsigned char*[png_data.height];
	    for (unsigned int i = 0; i < png_data.height; ++i) {
		raw_data[i] = new unsigned char[png_data.stride];
	    }

	    png_read_image(png_ptr, raw_data);

	    ImageDataArray data_array(png_data.height * png_data.stride);

	    //	    unsigned int k{0};
	    for (unsigned int i = 0; i < png_data.height; ++i) {
		for (unsigned int j = 0; j < png_data.stride; ++j) {
		    data_array[i * png_data.stride + j] = raw_data[i][j];
		    // DEBUG_PRINT("flat index: [%d]\t 2dim index: [%d][%d]\n",
		    // 		i * data.stride + j,
		    // 		i, j);
		}
	    }

	    png_data.data = data_array;

	    for (unsigned int i = 0; i < png_data.height; ++i) {
		delete[] raw_data[i];
	    }
	    
	    delete[] raw_data;
	}
    }

    return png_data;
}

bool ImageLoader::write_data(const std::string& filename, const ImageData& imgdata)
{
    FILE* file = fopen(filename.c_str(), "w");
    if (!file) return false;

    FilePtr file_ptr{file, std::fclose};

    png_structp png_ptr =
	png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return false;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) return false;

    png_init_io(png_ptr, file_ptr.get());

    png_set_IHDR(png_ptr, info_ptr, imgdata.width, imgdata.height,
		 imgdata.bit_depth, imgdata.color_type, PNG_INTERLACE_NONE,
		 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    unsigned char** raw_data = new unsigned char*[imgdata.height];
    for (unsigned int i = 0; i < imgdata.height; ++i) {
	raw_data[i] = new unsigned char[imgdata.stride];
    }

    for (unsigned int i = 0; i < imgdata.height; ++i) {
	for (unsigned int j = 0; j < imgdata.stride; ++j) {
	    raw_data[i][j] = imgdata.data[i * imgdata.stride + j];
	}
    }    

    if (setjmp(png_jmpbuf(png_ptr))) {
	_abort("[write_png_file] Error during writing bytes");
    }
    
    png_write_image(png_ptr, raw_data);

    if (setjmp(png_jmpbuf(png_ptr))) {
	_abort("[write_png_file] Error during end of write");
    }    

    png_write_end(png_ptr, nullptr);

    fprintf(stdout, "First stride\n");
    for (unsigned int i = 0; i < 20; ++i) {
    	fprintf(stdout, "0x%1x ", static_cast<unsigned int>(imgdata.data[i]));
    }
    fprintf(stdout, "\n");

    for (unsigned int i = 0; i < imgdata.height; ++i) {
	delete[] raw_data[i];
    }    

    delete[] raw_data;

    return true;
}

bool ImageLoader::_check_format()
{
    unsigned char pngtag[8];

    if (!std::fread(pngtag,
		   sizeof(unsigned char),
		   sizeof(pngtag) / sizeof(unsigned char),
		   _pfile.get())) {
	_error = ImageLoaderError::FileReadError;
	return false;
    }

    if (png_sig_cmp(pngtag, 0, sizeof(pngtag))) {
	return false;
    }

    return true;
}

void ImageLoader::_abort(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr,s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}
