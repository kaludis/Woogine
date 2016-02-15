#pragma once

#include "renderer/abstractrenderer.h"
#include "window/abstractwindow.h"
#include "camera/abstractcamera.h"
#include "input/input.h"
#include "controller/abstractcontroller.h"

#include "scene.h"

#include <chrono>

class Core {
public:
    Core()
	: _pscene{nullptr},
	_prenderer{nullptr},
	_pwindow{nullptr},
	_is_init{false},
	_is_running{true},
	_show_fps{false},
	_fps{0},
	_start{std::chrono::system_clock::now()}
    {}
    
    void set_renderer(IRendererPtr&& renderer);

    void set_window(IWindowPtr&& window);

    void set_camera(ICameraPtr&& camera);

    void set_input(InputPtr&& input);

    void set_controller(IControllerPtr&& controller);
    
    bool is_running() const;

    void run_scene(ScenePtr& scene);

    void show_fps(bool show);

private:
    void _init();
    
    float _time_elapsed();
    
    void _poll_events(Input& input);
    
private:
    ScenePtr _pscene;
    IRendererPtr _prenderer;
    IWindowPtr _pwindow;
    ICameraPtr _pcamera;
    InputPtr _pinput;
    IControllerPtr _pcontroller;

    bool _is_init;
    bool _is_running;

    bool _show_fps;
    unsigned int _fps;
    std::chrono::system_clock::time_point _start;
};

inline
bool Core::is_running() const
{   
    return _is_running;
}

inline
void Core::set_renderer(IRendererPtr&& renderer)
{
    _prenderer.swap(renderer);
}

inline
void Core::set_window(IWindowPtr&& window)
{
    _pwindow.swap(window);
}

inline
void Core::set_camera(ICameraPtr&& camera)
{
    _pcamera.swap(camera);
}

inline
void Core::set_input(InputPtr&& input)
{
    _pinput.swap(input);
}

inline
void Core::set_controller(IControllerPtr&& controller)
{
    _pcontroller.swap(controller);
}

inline
void Core::show_fps(bool show)
{
    _show_fps = show;
}
