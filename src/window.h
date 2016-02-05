#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <functional>
#include <tuple>

class Window {
public:
    struct WindowSize {
	float width;
	float height;
    };    

private:
    struct CtxWrapper {
	SDL_GLContext ctx;
    };
    
    using OGLWindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using OGLContextPtr = std::unique_ptr<CtxWrapper, std::function<void(CtxWrapper*)>>;
    
public:
    Window();
    void swap_window();

    void resize(int width, int height);

    WindowSize size() const;

private:
    void _init();
    
private:
    OGLWindowPtr _pwindow;
    OGLContextPtr _poglctx;
    int _width;
    int _height;
};

using WindowPtr = std::unique_ptr<Window>;

inline
Window::WindowSize Window::size() const
{
    return WindowSize{static_cast<float>(_width),
	    static_cast<float>(_height)};
}
