#pragma once

#include <memory>

class Entity;
class IWindow;
class ICamera;
class Text;

class IRenderer {
public:
    ~IRenderer() {}

    virtual void render(const Entity& entity) = 0;

    virtual void render_text(const Text& text) = 0;

    virtual void reset() = 0;

    virtual void set_window(IWindow* window) = 0;

    virtual void set_camera(ICamera* camera) = 0;
};

using IRendererPtr = std::unique_ptr<IRenderer>;
