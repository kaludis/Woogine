#pragma once

#include "programrawdata.h"

#include <string>

class ProgramDataReader {
public:
    ProgramRawDataPtr read_program_data(const std::string& vs_filename,
					const std::string& fs_filename);
    
private:
    std::string load_shader_source(const std::string& file_name);
};
