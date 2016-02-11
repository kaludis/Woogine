#pragma once

#include "scene.h"
#include "entity.h"
#include "sprite.h"
#include "camera.h"
#include "window.h"
#include "textmanager.h"

#include <memory>
#include <limits>

#include <glm/glm.hpp>

class Renderer {
public:
    using TextManagerPtr = std::unique_ptr<TextManager>;

public:
    Renderer();
    
    void render_scene(const ScenePtr& scene, const CameraPtr& camera);

    void set_window(Window* window);
    
private:
    void _reset_state();

    void _render_entity(const Entity& entity);

    void _render_sprite(const Sprite& sprite);

    void _render_text(const Text& text);

    glm::mat4 _projection_matrix() const;

    void _use_program(const Program& program);

    void _pass_viewprojection(const glm::mat4& projection,
			      const glm::mat4& view);

private:
    Window* _pwindow;
    TextManagerPtr _ptxtman;
    // current OGL state
    Program _program;
    GLuint _buffer;
    GLuint _indexbuffer;
    GLuint _index_count;
    GLuint _tex;
};

using RendererPtr = std::unique_ptr<Renderer>;

inline
Renderer::Renderer()
    : _ptxtman{new TextManager{"../fonts/DejaVuSansMono.ttf"}}
{
    _reset_state();
}

inline
void Renderer::set_window(Window* window)
{
    _pwindow = window;
}

