#include "resourcemanager.h"
#include "../exceptions/resourcemanagerexception.h"
#include "../defs/vertexattributes.h"

#include "../utils/utils.h"
#include "../debug/debug.h"

#include <limits>
#include <algorithm>

using namespace utils::debug;

ResourceManager::~ResourceManager()
{
    _release_resources();
}

Program ResourceManager::entity_program(const std::string& vs_name,
					const std::string& fs_name)
{
    std::string prog_name = vs_name + fs_name;
    auto it = _program_map.find(prog_name);
    if (it == _program_map.end()) {
	ProgramRawDataPtr prog_rd =
	    _pprogdatareader->read_program_data(vs_name, fs_name);

	Program new_program = _create_program(prog_rd);
	
	_program_map[prog_name] = new_program;
	return new_program;
    } else {
	return it->second;
    }
}

Mesh ResourceManager::entity_mesh(const std::string& mesh_name)
{
    auto it = _mesh_map.find(mesh_name);
    if (it == _mesh_map.end()) {
	//	std::string mesh_file = _pfsresolver->mesh_file(entity_type);
	
	MeshRawDataPtr mesh_rd = _pmeshdatareader->read_mesh_data(mesh_name);
	
	Mesh new_mesh = _create_mesh(mesh_rd);
	
	unsigned int max = std::numeric_limits<unsigned int>::max();
	
	if (new_mesh.buffer_id == max ||
	    new_mesh.indexbuffer_id == max ||
	    new_mesh.index_count == max) {
	    throw ResourceManagerException{"Could not create OpenGL buffers for mesh"};
	}
	    
	_mesh_map[mesh_name] = new_mesh;
	return new_mesh;
    } else {
	return it->second;
    }
}

Texture ResourceManager::entity_texture(const std::string& texture_name)
{
    auto it = _texture_map.find(texture_name);
    if (it == _texture_map.end()) {
	//	std::string tex_file = _pfsresolver->texture_file(entity_type);
	
	TextureRawDataPtr tex_rd = _ptexdatareader->read_texture_data(texture_name);
	
	Texture new_tex = _create_texture(*tex_rd);
	
	unsigned int max = std::numeric_limits<unsigned int>::max();
	
	if (new_tex.tex_id == max) {
	    throw ResourceManagerException{"Could not create OpenGL texture"};
	}
    
	_texture_map[texture_name] = new_tex;
	return new_tex;
    } else {
	return it->second;
    }
}

Sprite ResourceManager::entity_sprite(const std::string& sprite_name)
{
    auto it = _sprite_map.find(sprite_name);
    if (it == _sprite_map.end()) {
	SpriteRawDataPtr sprite_rd = _pspritedatareader->read_sprite_data(sprite_name);

	Texture new_tex = _create_texture(sprite_rd->texture_data);
	// TODO: Handling errors

	SpritePtr sprite = _create_sprite(*sprite_rd);
	sprite->_texture_id = new_tex.tex_id;

	_sprite_map[sprite_name] = *sprite;

	return *sprite;
    } else {
	return it->second;
    }
}

TextProgram ResourceManager::text_program(const std::string& vs_name,
		     const std::string& fs_name)
{
    std::string progname = vs_name + fs_name;
    auto it = _textprogrammap.find(progname);
    if (it == _textprogrammap.end()) {
	ProgramRawDataPtr prog_rd =
	    _pprogdatareader->read_program_data(vs_name, fs_name);

	GLuint vs_id = _create_shader(prog_rd->vs_source, GL_VERTEX_SHADER);
	if (!vs_id) ResourceManagerException{"Text vertex shader compile error"};

	GLuint fs_id = _create_shader(prog_rd->fs_source, GL_FRAGMENT_SHADER);
	if (!fs_id) throw ResourceManagerException{"Text fragment shader compile error"};

	TextProgram text_program;
	
	text_program.program_id = _link_program(vs_id, fs_id);
	if (!text_program.program_id)
	    throw ResourceManagerException{"Text shader program link error"};

	text_program.uniform_projection = _uniform_location(text_program.program_id, "projection");
	if (text_program.uniform_projection == -1) {
	    throw ResourceManagerException{"Could not get uniform location " \
		    "for 'projection' uniform in text shader"};
	}

	text_program.uniform_glyph = _uniform_location(text_program.program_id, "glyph");
	if (text_program.uniform_glyph == -1) {
	    throw ResourceManagerException{"Could not get uniform location " \
		    "for 'glyph' uniform in text shader"};
	}

	text_program.uniform_textcolor = _uniform_location(text_program.program_id, "textcolor");
	if (text_program.uniform_textcolor == -1) {
	    throw ResourceManagerException{"Could not get uniform location " \
		    "for 'textcolor' uniform in text shader"};
	}		

	text_program.attribute_texcoord = _attrib_location(text_program.program_id, "texcoord");
	if (text_program.attribute_texcoord == -1) {
	    throw ResourceManagerException{"Could not get uniform location " \
		    "for 'textcoord' uniform in text shader"};
	}

	_textprogrammap[progname] = text_program;
	return text_program;
    } else {
	return it->second;
    }    
}

TextMesh ResourceManager::text_mesh()
{
    auto it = _textmeshmap.find("text");
    if (it == _textmeshmap.end()) {
	TextMesh text_mesh;

	//	glGenVertexArrays(1, &text_mesh.vao);
	glGenBuffers(1, &text_mesh.vbo);
	
	//	glBindVertexArray(text_mesh.vao);
	//	if (glIsVertexArray(text_mesh.vao) != GL_TRUE) {
	//	    throw ResourceManagerException("Invalid VAO for textmesh");
	//	}
	
	glBindBuffer(GL_ARRAY_BUFFER, text_mesh.vbo);
	if (glIsBuffer(text_mesh.vbo) != GL_TRUE) {
	    throw ResourceManagerException{"Invalid VBO for text mesh"};
	}

	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	//	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);
	CHECK_ERR();

	_textmeshmap["text"] = text_mesh;
	return text_mesh;
    } else {
	return it->second;
    }
}

Program ResourceManager::_create_program(const ProgramRawDataPtr& prog_rd)
{
    Program new_prog{0, -1, -1, -1, -1, -1, -1};
    
    GLuint vs_id = _create_shader(prog_rd->vs_source, GL_VERTEX_SHADER);

    if (!vs_id) throw ResourceManagerException{"Vertex shader compile error"};

    GLuint fs_id = _create_shader(prog_rd->fs_source, GL_FRAGMENT_SHADER);
    if (!fs_id) throw ResourceManagerException{"Fragment shader compile error"};

    new_prog.program_id = _link_program(vs_id, fs_id);
    if (!new_prog.program_id) throw ResourceManagerException{"Shader program link error"};

    new_prog.attrib_coord3d = _attrib_location(new_prog.program_id, "coord3d");
    if (new_prog.attrib_coord3d == -1) {
	throw ResourceManagerException{"Could not get attribute location for 'coord3d' attribute"};
    }

    new_prog.attrib_texcoord = _attrib_location(new_prog.program_id, "texcoord");
    if (new_prog.attrib_texcoord == -1) {
	throw ResourceManagerException{"Could not get attribute location for 'texcoord' attribute"};
    }

    new_prog.uniform_projection = _uniform_location(new_prog.program_id, "projection");
    if (new_prog.uniform_projection == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'projection' uniform"};
    }

    new_prog.uniform_view = _uniform_location(new_prog.program_id, "view");
    if (new_prog.uniform_view == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'view' uniform"};
    }

    new_prog.uniform_model = _uniform_location(new_prog.program_id, "model");
    if (new_prog.uniform_model == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'model' uniform"};
    }    

    new_prog.uniform_sampler2d = _uniform_location(new_prog.program_id, "sampler2d");    
    if (new_prog.uniform_sampler2d == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'sampler2d' uniform"};
    }

    return new_prog;
}

Mesh ResourceManager::_create_mesh(const MeshRawDataPtr& mesh_rd)
{
    GLuint vbo_ids[3];

    glGenBuffers(3, vbo_ids);
    CHECK_ERR();

    //    std::vector<Vertex3dAttrib> hybrid_data;
    std::size_t vertex_count = mesh_rd->vertices.size() / 3;

    // for (std::size_t i = 0; i < vertex_count; ++ i) {
    // 	hybrid_data.emplace_back(Vertex3dAttrib{
    // 		{mesh_rd->vertices[i * 3], mesh_rd->vertices[i * 3 + 1], mesh_rd->vertices[i * 3 + 2]},
    // 		    {mesh_rd->texuvcoords[i * 2], mesh_rd->texuvcoords[i * 2 + 1]}
    // 	    });
    // }

    std::vector<Vertex3dAttrib> packed_va;
    for (std::size_t i = 0; i < vertex_count; ++i) {
	packed_va.emplace_back(Vertex3dAttrib{
		mesh_rd->vertices[i * 3],
		    mesh_rd->vertices[i * 3 + 1],
		    mesh_rd->vertices[i * 3 + 2]});
    }

    std::size_t uvtex_count = mesh_rd->texuvcoords.size() / 2;
    std::vector<UVCoords> packed_tex;
    for (std::size_t i = 0; i < uvtex_count; ++i) {
	packed_tex.emplace_back(UVCoords{
		mesh_rd->texuvcoords[i * 2],
		    mesh_rd->texuvcoords[i * 2 + 1]});
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
    CHECK_ERR();
    
    glBufferData(GL_ARRAY_BUFFER,
		 // hybrid_data.size() * sizeof(Vertex3dAttrib),
		 //hybrid_data.data(),
		 packed_va.size() * sizeof(Vertex3dAttrib),
		 packed_va.data(),
		 GL_STATIC_DRAW);
    CHECK_ERR();

    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
    CHECK_ERR();
    
    glBufferData(GL_ARRAY_BUFFER,
		 packed_tex.size() * sizeof(UVCoords),
		 packed_tex.data(),
		 GL_STATIC_DRAW);
    CHECK_ERR();    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
    CHECK_ERR();    
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    		 mesh_rd->indices.size() * sizeof(unsigned short),
    		 mesh_rd->indices.data(),
    		 GL_STATIC_DRAW);
    CHECK_ERR();

    if ((glIsBuffer(vbo_ids[0]) != GL_TRUE)
	|| (glIsBuffer(vbo_ids[1]) != GL_TRUE)
	|| (glIsBuffer(vbo_ids[2]) != GL_TRUE)) {
	return Mesh {
	    std::numeric_limits<unsigned int>::max(),
		std::numeric_limits<unsigned int>::max(),
		std::numeric_limits<unsigned int>::max(),
		0
	};
    }    

    return Mesh{vbo_ids[0], vbo_ids[1], vbo_ids[2],  static_cast<GLuint>(mesh_rd->indices.size())};
}

Texture ResourceManager::_create_texture(const TextureRawData& tex_rd)
{
    GLuint tex_id{0};
    
    glGenTextures(1, &tex_id);
    CHECK_ERR();
    
    glBindTexture(GL_TEXTURE_2D, tex_id);
    CHECK_ERR();
    
    if (glIsTexture(tex_id) != GL_TRUE) {
	return Texture{std::numeric_limits<unsigned int>::max()};
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    CHECK_ERR();
    
    glTexImage2D(
		 GL_TEXTURE_2D,
		 0,
		 GL_RGBA,
		 tex_rd.width,
		 tex_rd.height,
		 0,
		 GL_RGBA,
		 GL_UNSIGNED_BYTE,
		 tex_rd.data.data()
		 );
    CHECK_ERR();

    return Texture{tex_id};
}

SpritePtr ResourceManager::_create_sprite(const SpriteRawData& sprite_rd)
{
    GLuint vbo_id;

    glGenBuffers(1, &vbo_id);
    CHECK_ERR();

    SpritePtr sprite{new Sprite};

    unsigned int rows = sprite_rd.sprites_rows;
    unsigned int cols = sprite_rd.sprites_stride;
    unsigned int count = sprite_rd.sprites_count;

    float step_xuv = 1.0f / cols;
    float step_yuv = 1.0f / rows;

    /*
      3 (0, 1) ----------(1, 1) 2
           |                |
	   |                |
	   |                |
  	   |                |
      0 (0, 0)-----------(1, 0) 1
     */

    Sprite::QuadUV quaduv;
    quaduv.bottom_left.uvcoord[0] = -step_xuv;
    quaduv.bottom_left.uvcoord[1] = 1.0f;
    quaduv.bottom_right.uvcoord[0] = 0.0f;
    quaduv.bottom_right.uvcoord[1] = 1.0f;
    quaduv.top_right.uvcoord[0] = 0.0f;
    quaduv.top_right.uvcoord[1] = 1.0f + step_yuv;
    quaduv.top_left.uvcoord[0] = -step_xuv;
    quaduv.top_left.uvcoord[1] = 1.0f + step_yuv;

    for (unsigned int i = 0; i < rows; ++i) {
	quaduv.bottom_left.uvcoord[1] -= step_yuv;
	quaduv.bottom_right.uvcoord[1] -= step_yuv;
	quaduv.top_right.uvcoord[1] -= step_yuv;
	quaduv.top_left.uvcoord[1] -= step_yuv;
	
	for (unsigned int j = 0; j < cols; ++j) {
	    quaduv.bottom_left.uvcoord[0] += step_xuv;
	    quaduv.bottom_right.uvcoord[0] += step_xuv;
	    quaduv.top_right.uvcoord[0] += step_xuv;
	    quaduv.top_left.uvcoord[0] += step_xuv;
	    
	    sprite->_quaduvlist.push_back(quaduv);
	    
	    if (!--count) {
		i = rows;
		break;
	    }
	}

	quaduv.bottom_left.uvcoord[0] = -step_xuv;
	quaduv.bottom_right.uvcoord[0] = 0.0f;
	quaduv.top_right.uvcoord[0] = 0.0f;
	quaduv.top_left.uvcoord[0] = -step_xuv;
    }

    //    std::reverse(sprite->_quaduvlist.begin(), sprite->_quaduvlist.end());

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    if (glIsBuffer(vbo_id) != GL_TRUE) {
	return SpritePtr{nullptr};
    }

    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(Sprite::QuadUV),
		 &sprite->_quaduvlist[0],
		 GL_DYNAMIC_DRAW);
    CHECK_ERR();

    sprite->_buffer_id = vbo_id;

    return sprite;
}

GLuint ResourceManager::_create_shader(const std::string& shader_source, GLenum type)
{
	GLint compile_ok{GL_FALSE};
	GLuint shader_id = glCreateShader(type);
	CHECK_ERR();
	
	const char* shader_source_c = shader_source.c_str();
	
	glShaderSource(shader_id, 1, &shader_source_c, nullptr);
        CHECK_ERR();
	
	glCompileShader(shader_id);
	CHECK_ERR();
	
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_ok);
	CHECK_ERR();
	
	if (compile_ok != GL_TRUE) {
		switch (type) {
			case GL_VERTEX_SHADER:
			    DEBUG_MSG("Error in vertex shader:");
				break;
			case GL_FRAGMENT_SHADER:
			    DEBUG_MSG("Error in fragment shader: ");
				break;
		}

		_print_log(shader_id);

		shader_id = std::numeric_limits<unsigned int>::max();
	}

	return shader_id;    
}

GLuint ResourceManager::_link_program(GLuint vs_id, GLuint fs_id)
{
	GLint link_ok{GL_FALSE};
	
	GLuint program_id = glCreateProgram();
	CHECK_ERR();
	
	glAttachShader(program_id, vs_id);
	CHECK_ERR();
	
	glAttachShader(program_id, fs_id);
	CHECK_ERR();
	
	glLinkProgram(program_id);
	CHECK_ERR();
	
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_ok);
	CHECK_ERR();

	if (link_ok != GL_TRUE) {
	    DEBUG_MSG("Error with program linking:");
	    _print_log(program_id);
	    program_id = std::numeric_limits<unsigned int>::max();
	}

	return program_id;
}

void ResourceManager::_print_log(GLuint object)
{
	GLint log_len {0};

	if (glIsShader(object)) {
	    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_len);
	    CHECK_ERR();
	} else if (glIsProgram(object)) {
	    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_len);
	    CHECK_ERR();
	} else {
	    DEBUG_MSG("Log: Object is not a shader or a program");
	    return;
	}

	std::vector<char> log(log_len);

	if (glIsShader(object)) {
		glGetShaderInfoLog(object, log_len, nullptr, log.data());
		CHECK_ERR();
	} else if (glIsProgram(object)) {
		glGetProgramInfoLog(object, log_len, nullptr, log.data());
		CHECK_ERR();
	}

	std::string log_text{std::begin(log), std::end(log)};
	DEBUG_PRINT("%s\n", log_text.c_str());
}

GLint
ResourceManager::_attrib_location(GLuint program_id,
				     const std::string& attrib_name)
{
    GLint attrib_id = glGetAttribLocation(program_id, attrib_name.c_str());
    CHECK_ERR();
    return attrib_id;
}

GLint
ResourceManager::_uniform_location(GLuint program_id,
				      const std::string& uniform_name)
{
    GLint uniform_id = glGetUniformLocation(program_id, uniform_name.c_str());
    CHECK_ERR();
    return uniform_id;
}

void ResourceManager::_release_resources()
{
    if (_program_map.size()) {
	for (auto& pair : _program_map) {
	    if (glIsProgram(pair.second.program_id) == GL_TRUE) {
		glDeleteProgram(pair.second.program_id);
		CHECK_ERR();
	    }
	}
    }

    if (_mesh_map.size()) {
	for (auto& pair : _mesh_map) {
	    if (glIsBuffer(pair.second.buffer_id) == GL_TRUE) {
		glDeleteBuffers(1, &pair.second.buffer_id);
	    }

	    if (glIsBuffer(pair.second.indexbuffer_id) == GL_TRUE) {
		glDeleteBuffers(1, &pair.second.indexbuffer_id);
	    }

	    if (glIsBuffer(pair.second.texbuffer_id == GL_TRUE)) {
		glDeleteBuffers(1, &pair.second.texbuffer_id);
	    }
	    CHECK_ERR();	    
	}
    }

    if (_texture_map.size()) {
	for (auto& pair : _texture_map) {
	    if (glIsTexture(pair.second.tex_id) == GL_TRUE) {
		glDeleteTextures(1, &pair.second.tex_id);
		CHECK_ERR();
	    }
	}
    }

    if (_textprogrammap.size()) {
	for (auto& pair : _textprogrammap) {
	    if (glIsProgram(pair.second.program_id) == GL_TRUE) {
		glDeleteProgram(pair.second.program_id);
		CHECK_ERR();
	    }
	}
    }

    if (_textmeshmap.size()) {
	for (auto& pair : _textmeshmap) {
	    if (glIsVertexArray(pair.second.vao) == GL_TRUE) {
		glDeleteVertexArrays(1, &pair.second.vao);
	    }

	    if (glIsBuffer(pair.second.vbo) == GL_TRUE) {
		glDeleteBuffers(1, &pair.second.vbo);
	    }
	    CHECK_ERR();
	}
    }
}
