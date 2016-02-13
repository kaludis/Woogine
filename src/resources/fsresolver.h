#pragma once

#include <string>
#include <fstream>

class FSResolver {
public:
    struct ProgramFiles {
	std::string vs_file;
	std::string fs_file;
    };

public:
    FSResolver()
	: _datafile{},
	_entity_type{}
    {}

    void set_datafile(const std::string& datafile);

    ProgramFiles program_files(const std::string& entity_type);

    std::string mesh_file(const std::string& entity_type);

    std::string texture_file(const std::string& entity_type);

private:
    void fill_data();
    
private:
    std::string _datafile;
    std::string _entity_type;

    ProgramFiles _program_files;
    std::string _mesh_file;
    std::string _texture_file;
};

inline
void FSResolver::set_datafile(const std::string& datafile)
{
    _datafile = datafile;
}
