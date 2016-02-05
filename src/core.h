#pragma once

#include "renderer.h"
#include "scene.h"
#include "window.h"
#include "camera.h"

class Core {
public:
    Core()
	: _pscene{nullptr},
	_prenderer{nullptr},
	_pwindow{nullptr},
	_is_running{true}
    {}
    
    void set_renderer(RendererPtr&& renderer);

    void set_window(WindowPtr&& window);

    void set_camera(CameraPtr&& camera);
    
    bool is_running() const;

    void run_scene(ScenePtr& scene);

private:
    float _time_elapsed();
    void _process_events();
    
private:
    ScenePtr _pscene;
    RendererPtr _prenderer;
    WindowPtr _pwindow;
    CameraPtr _pcamera;
    bool _is_running;
};

inline
bool Core::is_running() const
{   
    return _is_running;
}

inline
void Core::set_renderer(RendererPtr&& renderer)
{
    _prenderer.swap(renderer);
    _prenderer->set_window(_pwindow.get());
}

inline
void Core::set_window(WindowPtr&& window)
{
    _pwindow.swap(window);
}

inline
void Core::set_camera(CameraPtr&& camera)
{
    _pcamera.swap(camera);
}
