#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include <cstdio>
#include <cstdarg>

#include <png.h>

class ImageLoader {
public:
    enum class ImageLoaderError {
	None,
	    FileNotExists,
	    FileReadError,
	    BadFileFormat,
	    LibraryError
    };

    using ImageDataArray = std::vector<unsigned char>;
    using FilePtr = std::unique_ptr<std::FILE, decltype(*std::fclose)>;

    struct ImageData {
	ImageDataArray data;	
	unsigned int width;
	unsigned int height;
	unsigned int nutes;
	unsigned int stride;
	unsigned int bit_depth;
	unsigned int color_type;
    };    

public:
    ImageLoader()
	: _filename{},
	_error{ImageLoaderError::None},
	_pfile{nullptr, std::fclose}
    {}

    ImageLoader(const std::string& filename)
	: _filename{filename},
	_error{ImageLoaderError::None},
	_pfile{nullptr, std::fclose}	
    {}

    ImageData read_data(const std::string& filename = std::string{});

    bool write_data(const std::string& filename, const ImageData& imgdata);

private:
    bool _check_format();
    void _abort(const char* s, ...);

private:
    std::string _filename;
    ImageLoaderError _error;
    FilePtr _pfile;
};

