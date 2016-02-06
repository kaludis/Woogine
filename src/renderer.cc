#include "renderer.h"
#include "entityresources.h"
#include "program.h"
#include "mesh.h"
#include "texture.h"
#include "vertexattributes.h"
#include "debug.h"

#include <cstddef>

#include <GL/gl.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Renderer::render_scene(const ScenePtr& scene, const CameraPtr& camera)
{
    _reset_state();

    for (const Entity& entity : *(scene->entity_list())) {
	_use_program(entity.resources().program);	
	_pass_viewprojection(_projection_matrix(), camera->view_matrix());
	_render_entity(entity);
    }
}    
    
void Renderer::_render_entity(const Entity& entity)
{
    const EntityResources& res = entity.resources();

    glUniformMatrix4fv(
		       res.program.uniform_model,
		       1,
		       GL_FALSE,
		       glm::value_ptr(entity.model_matrix())
		       );

    _render_sprite(res.sprite);
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(res.program.uniform_sampler2d, 0);
    // glBindTexture(GL_TEXTURE_2D, res.texture.tex_id);

    // glBindBuffer(GL_ARRAY_BUFFER, res.mesh.texbuffer_id);
    // glEnableVertexAttribArray(res.program.attrib_texcoord);
    // glVertexAttribPointer(
    // 			  res.program.attrib_texcoord,
    // 			  2,
    // 			  GL_FLOAT,
    // 			  GL_FALSE,
    // 			  sizeof(UVCoords),
    // 			  BUFFER_OFFSET(offsetof(UVCoords, uvcoord))
    // 			  );    

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res.mesh.indexbuffer_id);
    
    glDrawElements(GL_TRIANGLES, res.mesh.index_count, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(res.program.attrib_texcoord);    
    glDisableVertexAttribArray(res.program.attrib_coord3d);

    CHECK_ERR();    
}

void Renderer::_reset_state()
{
    using namespace std;
    
    _program.program_id = numeric_limits<unsigned int>::max();
    _buffer = numeric_limits<unsigned int>::max();
    _indexbuffer = numeric_limits<unsigned int>::max();
    _index_count = numeric_limits<unsigned int>::max();
    _tex = numeric_limits<unsigned int>::max();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}

glm::mat4 Renderer::_projection_matrix() const
{
    Window::WindowSize wsize{800, 600};

    if (_pwindow) {
	wsize = _pwindow->size();
    }

    float aspect_ratio = wsize.width / wsize.height;

    return glm::ortho(-1 * aspect_ratio, aspect_ratio,
		      -1.0f, 1.0f, -1.0f, 1.0f);
}

void Renderer::_use_program(const Program& program)
{
    if (_program.program_id != program.program_id) {
	_program = program;
	glUseProgram(_program.program_id);	
    }
}

void Renderer::_pass_viewprojection(const glm::mat4& projection,
				    const glm::mat4& view)
{
    glUniformMatrix4fv(
		       _program.uniform_projection,
		       1,
		       GL_FALSE,
		       glm::value_ptr(projection)
		       );

    glUniformMatrix4fv(
		       _program.uniform_view,
		       1,
		       GL_FALSE,
		       glm::value_ptr(view)
		       );
}

void Renderer::_render_sprite(const Sprite& sprite)
{
    Sprite::QuadUV quaduv = sprite.quaduv();

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(_program.uniform_sampler2d, 0);
    glBindTexture(GL_TEXTURE_2D, sprite.texture_id());

    glBindBuffer(GL_ARRAY_BUFFER, sprite.buffer_id());
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(Sprite::QuadUV),
		 &quaduv,
		 GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(_program.attrib_texcoord);
    glVertexAttribPointer(
			  _program.attrib_texcoord,
			  2,
			  GL_FLOAT,
			  GL_FALSE,
			  sizeof(UVCoords),
			  BUFFER_OFFSET(offsetof(UVCoords, uvcoord))
			  );        
}
