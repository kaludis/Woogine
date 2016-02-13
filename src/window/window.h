#pragma once

#include "abstractwindow.h"
#include "windowsize.h"

#include <SDL2/SDL.h>

#include <memory>
#include <functional>
#include <tuple>

class Window : public IWindow {
private:
    struct CtxWrapper {
	SDL_GLContext ctx;
    };
    
    using OGLWindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using OGLContextPtr = std::unique_ptr<CtxWrapper, std::function<void(CtxWrapper*)>>;
    
public:
    Window();
    void swap_window() override;

    void resize(int width, int height) override;

    WindowSize size() const override;

private:
    void _init();
    
private:
    OGLWindowPtr _pwindow;
    OGLContextPtr _poglctx;
    int _width;
    int _height;
};

inline
WindowSize Window::size() const
{
    return WindowSize{static_cast<float>(_width),
	    static_cast<float>(_height)};
}
