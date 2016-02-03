#include "window.h"
#include "windowexc.h"
#include "debug.h"

#include <GL/glew.h>

#include <string>

Window::Window()
    : _pwindow{nullptr, SDL_DestroyWindow},
    _poglctx{nullptr, [](SDL_GLContext){}},
    _screen_width{1024},
    _screen_height{768}
{
    _init();
}

void Window::_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("3D Real-Time Rendering",
					  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					  _screen_width, _screen_height,
					  SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    CtxWrapper* ctxwrap = new CtxWrapper;    
    ctxwrap->ctx = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
    SDL_GL_MakeCurrent(window, ctxwrap->ctx);

    OGLWindowPtr wptr{window, SDL_DestroyWindow};
    _pwindow.swap(wptr);
    
    OGLContextPtr ctxptr{ctxwrap, [](CtxWrapper* ctxwrap){
	    SDL_GL_DeleteContext(ctxwrap->ctx);
	    delete ctxwrap;
	}};
    _poglctx.swap(ctxptr);

    GLenum glew_status = glewInit();

    if (glew_status != GLEW_OK) {
	const char* err =
	    static_cast<const char*>(static_cast<const void*>(glewGetErrorString(glew_status)));
	throw WindowException{std::string{"glewInit error: "}.append(err)};
    }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
}

void Window::swap_window()
{
    SDL_GL_SwapWindow(_pwindow.get());
}
