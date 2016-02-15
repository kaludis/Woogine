#include "renderer.h"
#include "../entity/entity.h"
#include "../resources/entityresources.h"
#include "../mesh/mesh.h"
#include "../texture/texture.h"
#include "../sprite/sprite.h"
#include "../defs/vertexattributes.h"
#include "../debug/debug.h"
#include "../text/text.h"

#include <cstddef>
#include <string>
#include <iostream>

#include <GL/gl.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Renderer::render(const Entity& entity)
{
    const EntityResources& eres = entity.resources();
    
    _use_program(eres.program);

    _pass_viewprojection(_projection_matrix(), _pcamera->view_matrix());    
    
    _render_entity(eres, entity.model_matrix());
}

void Renderer::_render_entity(const EntityResources& eres, const glm::mat4& model_matrix)
{
    glUniformMatrix4fv(eres.program.uniform_model,
		       1,
		       GL_FALSE,
		       glm::value_ptr(model_matrix));

    if (eres.sprite) {
	_render_sprite(*eres.sprite);
    } else {
	_render_texture(eres);
    }

    glBindBuffer(GL_ARRAY_BUFFER, eres.mesh.buffer_id);    
    glEnableVertexAttribArray(eres.program.attrib_coord3d);
    glVertexAttribPointer(eres.program.attrib_coord3d,
			  3,
			  GL_FLOAT,
			  GL_FALSE,
			  sizeof(Vertex3dAttrib),
			  BUFFER_OFFSET(offsetof(Vertex3dAttrib, coord3d)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eres.mesh.indexbuffer_id);
    
    glDrawElements(GL_TRIANGLES, eres.mesh.index_count, GL_UNSIGNED_SHORT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    glDisableVertexAttribArray(eres.program.attrib_texcoord);    
    glDisableVertexAttribArray(eres.program.attrib_coord3d);
    CHECK_ERR();    
}

void Renderer::render_text(const Text& text)
{
    std::string outtext = text.text();

    glUseProgram(text.program().program_id);
    CHECK_ERR();
    
    glUniformMatrix4fv(text.program().uniform_projection,
    		       1,
    		       GL_FALSE,
    		       glm::value_ptr(glm::ortho(0.0f, _pwindow->size().width, 0.0f, _pwindow->size().height)));
    CHECK_ERR();
    
    glActiveTexture(GL_TEXTURE1);
    glUniform3f(text.program().uniform_textcolor,
    		text.color().x,
    		text.color().y,
    		text.color().z);

    glUniform1i(text.program().uniform_glyph, 1);
    
    Point2f pos = text.position();

    for (std::string::size_type i = 0; i < outtext.length(); ++i) {
    	TextManager::Character ch = _ptxtman->character(outtext[i]);
	
    	GLfloat xpos = pos.xpos() + ch.bearing.x * text.scale();
    	GLfloat ypos = pos.ypos() - (ch.size.y - ch.bearing.y) * text.scale();

    	GLfloat w = ch.size.x * text.scale();
    	GLfloat h = ch.size.y * text.scale();

	w = w * text.scale();
	h = h * text.scale();

        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

    	glBindTexture(GL_TEXTURE_2D, ch.texture_id);	
    	glBindBuffer(GL_ARRAY_BUFFER, text.mesh().vbo);

	glEnableVertexAttribArray(text.program().attribute_texcoord);

	glVertexAttribPointer(text.program().attribute_texcoord,
			      4,
			      GL_FLOAT,
			      GL_FALSE,
			      4 * sizeof(GLfloat),
			      0);

	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(vertices),
		     &vertices,
		     GL_DYNAMIC_DRAW);
    	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(text.program().attribute_texcoord);	
    
    	pos.xpos() += (ch.advance >> 6) * text.scale();
    }

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_ERR();	    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    CHECK_ERR();	        
}

void Renderer::_render_texture(const EntityResources& eres)
{
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(eres.program.uniform_sampler2d, 0);
    glBindTexture(GL_TEXTURE_2D, eres.texture.tex_id);

    glBindBuffer(GL_ARRAY_BUFFER, eres.mesh.texbuffer_id);
    glEnableVertexAttribArray(eres.program.attrib_texcoord);
    glVertexAttribPointer(
    			  eres.program.attrib_texcoord,
    			  2,
    			  GL_FLOAT,
    			  GL_FALSE,
    			  sizeof(UVCoords),
    			  BUFFER_OFFSET(offsetof(UVCoords, uvcoord))
    			  );    
}
/*
void Renderer::render_scene(const ScenePtr& scene, const CameraPtr& camera)
{
    _reset_state();    
    
    for (const Entity& entity : scene->entity_list()) {

	_use_program(entity.resources().program);

	_render_entity(entity);
    }

    for (const auto& pair : scene->text_map()) {
	if (pair.second.text().length()) {
	    _render_text(pair.second);
	}
    }
}
  
void Renderer::_render_entity(const Entity& entity)
{
    const EntityResources& res = entity.resources();
    CHECK_ERR();
    glUniformMatrix4fv(
		       res.program.uniform_model,
		       1,
		       GL_FALSE,
		       glm::value_ptr(entity.model_matrix())
		       );
    CHECK_ERR();
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

    glBindTexture(GL_TEXTURE_2D, 0);
    
    glDisableVertexAttribArray(res.program.attrib_texcoord);    
    glDisableVertexAttribArray(res.program.attrib_coord3d);
    CHECK_ERR();
}
*/
void Renderer::reset()
{
    using namespace std;
    
    _program.program_id = numeric_limits<unsigned int>::max();
    _buffer = numeric_limits<unsigned int>::max();
    _indexbuffer = numeric_limits<unsigned int>::max();
    _index_count = numeric_limits<unsigned int>::max();
    _tex = numeric_limits<unsigned int>::max();

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}

glm::mat4 Renderer::_projection_matrix() const
{
    WindowSize wsize{800, 600};

    if (_pwindow) {
	wsize = _pwindow->size();
    }

    float aspect_ratio = wsize.width / wsize.height;

    //return glm::ortho(0.0f, wsize.width, 0.0f, wsize.height);
    return glm::ortho(-1 * aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f);
}

void Renderer::_use_program(const Program& program)
{
    if (_program.program_id != program.program_id) {
	_program = program;
	glUseProgram(_program.program_id);
	CHECK_ERR();
    }
}

void Renderer::_pass_viewprojection(const glm::mat4& projection,
				    const glm::mat4& view)
{
    glUniformMatrix4fv(_program.uniform_projection,
		       1,
		       GL_FALSE,
		       glm::value_ptr(projection));
    CHECK_ERR();
    glUniformMatrix4fv(_program.uniform_view,
		       1,
		       GL_FALSE,
		       glm::value_ptr(view));
        CHECK_ERR();
}

void Renderer::_render_sprite(const Sprite& sprite)
{
    Sprite::QuadUV quaduv = sprite.quaduv();

    glActiveTexture(GL_TEXTURE0);
    CHECK_ERR();
    glUniform1i(_program.uniform_sampler2d, 0);

    glBindTexture(GL_TEXTURE_2D, sprite.texture_id());

    glBindBuffer(GL_ARRAY_BUFFER, sprite.buffer_id());


    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(Sprite::QuadUV),
		 &quaduv,
		 GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(_program.attrib_texcoord);


    glVertexAttribPointer(_program.attrib_texcoord,
			  2,
			  GL_FLOAT,
			  GL_FALSE,
			  sizeof(UVCoords),
			  BUFFER_OFFSET(offsetof(UVCoords, uvcoord))
			  );
    CHECK_ERR();
}
/*
void Renderer::_render_text(const Text& text)
{
    std::string outtext = text.text();

    glUseProgram(text.program().program_id);
    CHECK_ERR();
    
    glUniformMatrix4fv(text.program().uniform_projection,
    		       1,
    		       GL_FALSE,
    		       glm::value_ptr(glm::ortho(0.0f, _pwindow->size().width, 0.0f, _pwindow->size().height)));
    CHECK_ERR();
    
    glActiveTexture(GL_TEXTURE1);
    glUniform3f(text.program().uniform_textcolor,
    		text.color().x,
    		text.color().y,
    		text.color().z);

    glUniform1i(text.program().uniform_glyph, 1);
    
    Point2f pos = text.position();

    for (std::string::size_type i = 0; i < outtext.length(); ++i) {
    	TextManager::Character ch = _ptxtman->character(outtext[i]);
	
    	GLfloat xpos = pos.xpos() + ch.bearing.x * text.scale();
    	GLfloat ypos = pos.ypos() - (ch.size.y - ch.bearing.y) * text.scale();

    	GLfloat w = ch.size.x * text.scale();
    	GLfloat h = ch.size.y * text.scale();

	w = w * text.scale();
	h = h * text.scale();

        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

    	glBindTexture(GL_TEXTURE_2D, ch.texture_id);	
    	glBindBuffer(GL_ARRAY_BUFFER, text.mesh().vbo);

	glEnableVertexAttribArray(text.program().attribute_texcoord);

	glVertexAttribPointer(text.program().attribute_texcoord,
			      4,
			      GL_FLOAT,
			      GL_FALSE,
			      4 * sizeof(GLfloat),
			      0);

	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(vertices),
		     &vertices,
		     GL_DYNAMIC_DRAW);
    	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(text.program().attribute_texcoord);	
    
    	pos.xpos() += (ch.advance >> 6) * text.scale();
    }

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_ERR();	    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    CHECK_ERR();	    
}
*/
