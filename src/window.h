#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <functional>

class Window {
private:
    struct CtxWrapper {
	SDL_GLContext ctx;
    };
    
    using OGLWindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using OGLContextPtr = std::unique_ptr<CtxWrapper, std::function<void(CtxWrapper*)>>;
    
public:
    Window();
    void swap_window();

private:
    void _init();
    
private:
    OGLWindowPtr _pwindow;
    OGLContextPtr _poglctx;
    int _screen_width;
    int _screen_height;
    
};

using WindowPtr = std::unique_ptr<Window>;
