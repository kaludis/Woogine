#include "core.h"

#include <chrono>

constexpr unsigned int msec_per_sec = 1000000;

void Core::run_scene(ScenePtr& scene)
{
    float dt = _time_elapsed();

    _process_events();
    
    scene->update(dt);

    _prenderer->render_scene(scene, _pcamera);

    _pwindow->swap_window();
}

void Core::_process_events()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
	switch (ev.type) {
	case SDL_QUIT:
	    _is_running = false;
	    break;
	case SDL_WINDOWEVENT:
	    switch (ev.window.event) {
	    case SDL_WINDOWEVENT_SIZE_CHANGED:
		_pwindow->resize(ev.window.data1, ev.window.data2);
		break;
	    }
	    break;
	}
    }    
}

float Core::_time_elapsed()
{
    using namespace std;

    chrono::system_clock::time_point now =
	chrono::system_clock::now();    
    static chrono::system_clock::time_point prev = now;

    float dt = chrono::duration_cast<chrono::microseconds>
	(now - prev).count() / msec_per_sec;
    
    prev = now;

    return (dt < 1.0f) ? 1.0f : dt;
}
