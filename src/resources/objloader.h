#pragma once

#include "objdata.h"

#include <fstream>

class ObjLoader {
public:
    enum class ObjLoaderError {
	None,
	    FileNotExists,
	    FileReadError,
	    BadFileFormat
    };

public:
    ObjLoader()
	: _error{ObjLoaderError::None}
    {}

    ObjDataPtr read_data(const std::string& filename);

    ObjLoaderError error() const;

private:
    template <typename T>
    T _read_attributes(const std::string& attr_type, std::ifstream& ifs);

private:
    ObjLoaderError _error;
};

inline
ObjLoader::ObjLoaderError ObjLoader::error() const
{
    return _error;
}
