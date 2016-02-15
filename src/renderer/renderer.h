#pragma once

#include "abstractrenderer.h"
#include "../scene.h"
#include "../camera/abstractcamera.h"
#include "../window/abstractwindow.h"
#include "../text/textmanager.h"
#include "../program/program.h"

#include <memory>
#include <limits>

#include <glm/glm.hpp>

class Entity;
struct EntityResources;
class Sprite;
class Camera;

class Renderer : public IRenderer {
public:
    using TextManagerPtr = std::unique_ptr<TextManager>;

public:
    Renderer();

    void render(const Entity& entity) override;

    void render_text(const Text& text) override;
    
    //void render_scene(const ScenePtr& scene, const CameraPtr& camera);

    void set_window(IWindow* window);

    void set_camera(ICamera* camera) override;
    
private:
    void _reset_state();

    //void _render_entity(const Entity& entity);

    void _render_entity(const EntityResources& eres, const glm::mat4& model_matrix);

    void _render_sprite(const Sprite& sprite);

    //void _render_text(const Text& text);

    glm::mat4 _projection_matrix() const;

    void _use_program(const Program& program);

    void _pass_viewprojection(const glm::mat4& projection,
			      const glm::mat4& view);

private:
    IWindow* _pwindow;
    ICamera* _pcamera;
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
void Renderer::set_window(IWindow* window)
{
    _pwindow = window;
}

inline
void Renderer::set_camera(ICamera* camera)
{
    _pcamera = camera;
}
