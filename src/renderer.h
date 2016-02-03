#pragma once

#include "scene.h"
#include "entity.h"
#include "camera.h"

#include <memory>
#include <limits>

#include <glm/glm.hpp>

class Renderer {
public:
    Renderer();
    
    void render_scene(const ScenePtr& scene, const CameraPtr& camera);
    
private:
    void _reset_state();

    void _render_entity(const Entity& entity, const glm::mat4& mvp);

private:
    // current OGL state
    GLuint _program;
    GLuint _buffer;
    GLuint _indexbuffer;
    GLuint _index_count;
    GLuint _tex;    
};

using RendererPtr = std::unique_ptr<Renderer>;

inline
Renderer::Renderer()
{
    _reset_state();
}
