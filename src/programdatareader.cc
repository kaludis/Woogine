#include "programdatareader.h"
#include "datareaderexception.h"

#include <fstream>
#include <string>

ProgramRawDataPtr
ProgramDataReader::read_program_data(const std::string& vs_filename,
					const std::string& fs_filename)
{
    std::string vs_source = load_shader_source(vs_filename);

    std::string fs_source = load_shader_source(fs_filename);

    if (!vs_source.size()) throw DataReaderException{"Vertex shader file '" +
				   vs_filename + "' are empty"};

    if (!fs_source.size()) throw DataReaderException{"Fragment shader file '" +
				   fs_filename + "' are empty"};

    ProgramRawData* pprogdata = new ProgramRawData{};
    pprogdata->vs_source = vs_source;
    pprogdata->fs_source = fs_source;

    return ProgramRawDataPtr{pprogdata};
}

std::string ProgramDataReader::load_shader_source(const std::string& filename)
{
	std::string shader_source{};

	std::ifstream ifs{filename};
	if (!ifs.is_open())
	    throw DataReaderException{"Shader file " +
		    filename +
		    " does not exists"};

	std::string source_line{};
	while (std::getline(ifs, source_line)) {
		shader_source.append(source_line).append("\n");
	}

	ifs.close();

	return shader_source;
}
