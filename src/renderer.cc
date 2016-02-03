#include "renderer.h"
#include "entityresources.h"
#include "program.h"
#include "mesh.h"
#include "texture.h"
#include "vertexattribute.h"
#include "debug.h"

#include <cstddef>

#include <GL/gl.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define BUFFER_OFFSET(idx)	\
	(static_cast<char*>(0) + idx)

constexpr int screen_width = 1024;
constexpr int screen_height = 768;

void Renderer::render_scene(const ScenePtr& scene, const CameraPtr& camera)
{
    _reset_state();

    for (const Entity& entity : *(scene->entity_list())) {
	glm::mat4 mvp = camera->projection_matrix() *
	    camera->view_matrix() *
	    entity.model_matrix();
	_render_entity(entity, mvp);
    }
}    
    
void Renderer::_render_entity(const Entity& entity, const glm::mat4& mvp)
{
    int size;
    
    const EntityResources& res = entity.resources();
    
    if (_program != res.program.program_id) {
	_program = res.program.program_id;
	glUseProgram(_program);
    }

    glUniformMatrix4fv(
		       res.program.uniform_mvp,
		       1,
		       GL_FALSE,
		       glm::value_ptr(mvp)
		       );

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(res.program.uniform_sampler2d, 0);
    glBindTexture(GL_TEXTURE_2D, res.texture.tex_id);

    glBindBuffer(GL_ARRAY_BUFFER, res.mesh.buffer_id);    
    glEnableVertexAttribArray(res.program.attrib_coord3d);
    glVertexAttribPointer(
			  res.program.attrib_coord3d,
			  3,
			  GL_FLOAT,
			  GL_FALSE,
			  sizeof(Vertex3dAttrib),
			  BUFFER_OFFSET(offsetof(Vertex3dAttrib, coord3d))
			  );

    //    glBindBuffer(GL_ARRAY_BUFFER, res.mesh.texbuffer_id);
    glEnableVertexAttribArray(res.program.attrib_texcoord);
    glVertexAttribPointer(
			  res.program.attrib_texcoord,
			  2,
			  GL_FLOAT,
			  GL_FALSE,
			  sizeof(Vertex3dAttrib),
			  BUFFER_OFFSET(offsetof(Vertex3dAttrib, uvcoord))
			  );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res.mesh.indexbuffer_id);
    
    glDrawElements(GL_TRIANGLES, res.mesh.index_count, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(res.program.attrib_coord3d);
    glDisableVertexAttribArray(res.program.attrib_texcoord);

    CHECK_ERR();    
}

void Renderer::_reset_state()
{
    using namespace std;
    
    _program = numeric_limits<unsigned int>::max();
    _buffer = numeric_limits<unsigned int>::max();
    _indexbuffer = numeric_limits<unsigned int>::max();
    _index_count = numeric_limits<unsigned int>::max();
    _tex = numeric_limits<unsigned int>::max();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}
