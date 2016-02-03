#include "resourcemanager.h"
#include "resourcemanagerexception.h"
#include "vertexattribute.h"

#include "utils.h"

#include <limits>
#include <iostream>

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
	// FSResolver::ProgramFiles pfiles =
	//     _pfsresolver->program_files(entity_type);

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
	
	Texture new_tex = _create_texture(tex_rd);
	
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

Program ResourceManager::_create_program(const ProgramRawDataPtr& prog_rd)
{
    Program new_prog{0, -1, -1, -1, -1};
    
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

    new_prog.uniform_mvp = _uniform_location(new_prog.program_id, "mvp");
    if (new_prog.uniform_mvp == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'mvp' uniform"};
    }

    new_prog.uniform_sampler2d = _uniform_location(new_prog.program_id, "sampler2d");    
    if (new_prog.uniform_sampler2d == -1) {
	throw ResourceManagerException{"Could not get uniform location for 'sampler2d' uniform"};
    }

    return new_prog;
}

Mesh ResourceManager::_create_mesh(const MeshRawDataPtr& mesh_rd)
{
    GLuint vbo_ids[2];

    glGenBuffers(2, vbo_ids);
    CHECK_ERR();

    std::vector<Vertex3dAttrib> hybrid_data;
    std::size_t vertex_count = mesh_rd->vertices.size() / 3;

    for (std::size_t i = 0; i < vertex_count; ++ i) {
    	hybrid_data.emplace_back(Vertex3dAttrib{
    		{mesh_rd->vertices[i * 3], mesh_rd->vertices[i * 3 + 1], mesh_rd->vertices[i * 3 + 2]},
    		    {mesh_rd->texuvcoords[i * 2], mesh_rd->texuvcoords[i * 2 + 1]}
    	    });
    }

    // for (int i = 0; i <  mesh_rd->texuvcoords.size(); i += 2) {
    // 	std::cout << mesh_rd->texuvcoords[i] << mesh_rd->texuvcoords[i + 1] << std::endl;
    // }


    // std::cout << "hybrid_data size: " << hybrid_data.size() << std::endl;
    
    // for (const Vertex3dAttrib& v : hybrid_data) {
    // 	std::cout << "{{"
    // 	     << v.coord3d[0] << ", "
    // 	     << v.coord3d[1] << ", "
    // 	     << v.coord3d[2] << "}, {"
    // 		  << v.uvcoord[0] << ", "
    // 		  << v.uvcoord[1] << "}}"
    // 		  << std::endl;
    // }

    float vertices[] = {
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0,  1.0,
	-1.0, -1.0,  1.0,
	-1.0, -1.0, -1.0,
	-1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,
	1.0, -1.0,  1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0,  1.0,  1.0	
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
    CHECK_ERR();
    
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER,
    // 		 mesh_rd->vertices.size() * sizeof(float),
    // 		 mesh_rd->vertices.data(),
    // 		 GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER,
		 hybrid_data.size() * sizeof(Vertex3dAttrib),
		 hybrid_data.data(),
		 GL_STATIC_DRAW);
    CHECK_ERR();

    

    float uvcoords[] = {
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,	
    };

    // glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
    // CHECK_ERR();
    
    // //    glBufferData(GL_ARRAY_BUFFER, sizeof(uvcoords), uvcoords, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER,
    // 		 mesh_rd->texuvcoords.size() * sizeof(float),
    // 		 mesh_rd->texuvcoords.data(),
    // 		 GL_STATIC_DRAW);    
    // CHECK_ERR();

    

    unsigned short indices[] = {
	0,  1,  2,
	2,  3,  0,
	4,  5,  6,
	6,  7,  4,
	8,  9, 10,
	10, 11,  8,
	12, 13, 14,
	14, 15, 12,
	16, 17, 18,
	18, 19, 16,
	20, 21, 22,
	22, 23, 20
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[1]);
    CHECK_ERR();    
    
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    		 mesh_rd->indices.size() * sizeof(unsigned short),
    		 mesh_rd->indices.data(),
    		 GL_STATIC_DRAW);
    CHECK_ERR();

    if ((glIsBuffer(vbo_ids[0]) != GL_TRUE) || (glIsBuffer(vbo_ids[1]) != GL_TRUE)) {
	return Mesh {
	    std::numeric_limits<unsigned int>::max(),
		std::numeric_limits<unsigned int>::max(),
		std::numeric_limits<unsigned int>::max()
	};
    }    

    return Mesh{vbo_ids[0], vbo_ids[1],  static_cast<GLuint>(mesh_rd->indices.size())};
}

Texture ResourceManager::_create_texture(const TextureRawDataPtr& tex_rd)
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
		 tex_rd->width,
		 tex_rd->height,
		 0,
		 GL_RGBA,
		 GL_UNSIGNED_BYTE,
		 tex_rd->data.data()
		 );
    CHECK_ERR();

    return Texture{tex_id};
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
    DEBUG_PRINT("Get new attribut location: %d\n", attrib_id);
    return attrib_id;
}

GLint
ResourceManager::_uniform_location(GLuint program_id,
				      const std::string& uniform_name)
{
    GLint uniform_id = glGetUniformLocation(program_id, uniform_name.c_str());
    CHECK_ERR();
    DEBUG_PRINT("Get new uniform location: %d\n", uniform_id);
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
		CHECK_ERR();
	    }

	    if (glIsBuffer(pair.second.indexbuffer_id) == GL_TRUE) {
		glDeleteBuffers(1, &pair.second.indexbuffer_id);
		CHECK_ERR();
	    }	    
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
}
