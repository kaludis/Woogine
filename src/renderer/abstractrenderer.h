#pragma once

#include <memory>

class IVisualEntity;
class IWindow;
class ICamera;
class Text;

class IRenderer {
public:
    ~IRenderer() {}

    virtual void render(const IVisualEntity& entity) = 0;

    virtual void render_text(const Text& text) = 0;

    virtual void set_window(IWindow* window) = 0;

    virtual void set_camera(ICamera* camera) = 0;
};

using IRendererPtr = std::unique_ptr<IRenderer>;
