#pragma once

#include "entityresources.h"

#include "program.h"
#include "mesh.h"
#include "texture.h"

#include "programdatareader.h"
#include "meshdatareader.h"
#include "texturedatareader.h"

#include "fsresolver.h"

#include <GL/glew.h>

#include <map>
#include <string>
#include <memory>

class ResourceManager {
private:
    using ProgramMap = std::map<std::string, Program>;
    using MeshMap = std::map<std::string, Mesh>;
    using TextureMap = std::map<std::string, Texture>;

    using ProgramDataReaderPtr = std::unique_ptr<ProgramDataReader>;
    using MeshDataReaderPtr = std::unique_ptr<MeshDataReader>;
    using TextureDataReaderPtr = std::unique_ptr<TextureDataReader>;
    using FSResolverPtr = std::unique_ptr<FSResolver>;

public:
    ResourceManager()
	: _pprogdatareader{new ProgramDataReader{}},
	_pmeshdatareader{new MeshDataReader{}},
	_ptexdatareader{new TextureDataReader{}},
	_pfsresolver{new FSResolver{}}
    {
	_pfsresolver->set_datafile("../data/entities.data");
    }

    ~ResourceManager();
    
    Program entity_program(const std::string& entity_type);

    Mesh entity_mesh(const std::string& entity_type);

    Texture entity_texture(const std::string& entity_type);

private:
    Program _create_program(const ProgramRawDataPtr& prog_rd);

    Mesh _create_mesh(const MeshRawDataPtr& mesh_rd);

    Texture _create_texture(const TextureRawDataPtr& tex_rd);

    GLuint _create_shader(const std::string& shader_source, GLenum type);

    GLuint _link_program(GLuint vs_id, GLuint fs_id);

    void _print_log(GLuint object);

    void _release_resources();    

private:
    ProgramDataReaderPtr _pprogdatareader;
    MeshDataReaderPtr _pmeshdatareader;
    TextureDataReaderPtr _ptexdatareader;
    FSResolverPtr _pfsresolver;
    
    ProgramMap _program_map;
    MeshMap _mesh_map;
    TextureMap _texture_map;
};
