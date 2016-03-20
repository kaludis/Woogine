#pragma once

#include "../resources/entityresources.h"

#include "../program/program.h"
#include "../program/textprogram.h"

#include "../mesh/mesh.h"
#include "../texture/texture.h"
#include "../sprite/sprite.h"

#include "../text/text.h"

#include "../resources/programdatareader.h"
#include "../resources/meshdatareader.h"
#include "../resources/texturedatareader.h"
#include "../resources/spritedatareader.h"

#include "../resources/fsresolver.h"

#include <GL/glew.h>

#include <map>
#include <string>
#include <memory>

class ResourceManager {
private:
    using ProgramMap = std::map<std::string, Program>;
    using MeshMap = std::map<std::string, Mesh>;
    using TextureMap = std::map<std::string, Texture>;
    using SpriteMap = std::map<std::string, SpritePtr>;

    using TextProgramMap = std::map<std::string, TextProgram>;    
    using TextMeshMap = std::map<std::string, TextMesh>;    

    using ProgramDataReaderPtr = std::unique_ptr<ProgramDataReader>;
    using MeshDataReaderPtr = std::unique_ptr<MeshDataReader>;
    using TextureDataReaderPtr = std::unique_ptr<TextureDataReader>;
    using SpriteDataReaderPtr = std::unique_ptr<SpriteDataReader>;
    //    using FSResolverPtr = std::unique_ptr<FSResolver>;

public:
    ResourceManager()
	: _pprogdatareader{new ProgramDataReader{}},
	_pmeshdatareader{new MeshDataReader{}},
	  _ptexdatareader{new TextureDataReader{}},
	  _pspritedatareader{new SpriteDataReader{}}
    {}

    ~ResourceManager();
    
    Program entity_program(const std::string& vs_name,
			   const std::string& fs_name);

    Mesh entity_mesh(const std::string& mesh_name);

    Texture entity_texture(const std::string& texture_name, const std::string& type);

    Sprite* entity_sprite(const std::string& sprite_name);

    TextProgram text_program(const std::string& vs_name,
			 const std::string& fs_name);

    TextMesh text_mesh();

private:
    Program _create_program(const ProgramRawDataPtr& prog_rd);

    GLint _attrib_location(GLuint program_id, const std::string& attrib_name);

    GLint _uniform_location(GLuint program_id, const std::string& uniform_name);    

    Mesh _create_mesh(const MeshRawDataPtr& mesh_rd);

    Texture _create_texture(const TextureRawData& tex_rd, 
			    TextureRawData::TextureType type = 
			    TextureRawData::TextureType::Simple);

    SpritePtr _create_sprite(const SpriteRawData& sprite_rd);

    GLuint _create_shader(const std::string& shader_source, GLenum type);

    GLuint _link_program(GLuint vs_id, GLuint fs_id);

    void _print_log(GLuint object);

    void _release_resources();    

private:
    ProgramDataReaderPtr _pprogdatareader;
    MeshDataReaderPtr _pmeshdatareader;
    TextureDataReaderPtr _ptexdatareader;
    SpriteDataReaderPtr _pspritedatareader;
    
    ProgramMap _program_map;
    MeshMap _mesh_map;
    TextureMap _texture_map;
    SpriteMap _sprite_map;

    TextProgramMap _textprogrammap;
    TextMeshMap _textmeshmap;    
};
