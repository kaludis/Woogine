#include "core.h"
#include "../debug/debug.h"

#include <SDL2/SDL.h>

#include <chrono>

constexpr unsigned int msec_per_sec = 1000000;

void Core::run_scene(ScenePtr& scene)
{
    if (!_is_init) {
	_is_init = true;
	_init();
    }

    ++_fps;
    
    float dt = _time_elapsed();

    _poll_events(*_pinput);

    scene->update(dt, *_pcontroller);

    _prenderer->reset();
    
    scene->render_scene(*_prenderer);

    _pwindow->swap_window();

    std::chrono::system_clock::time_point end =
	std::chrono::system_clock::now();

    if (std::chrono::duration_cast<std::chrono::microseconds>(end - _start)
	.count() / 1000000 >= 1) {
	_start = end;
	if (_show_fps) {
	    scene->reset_text("fps", std::to_string(_fps) + " fps");
	}	
	_fps = 0;
    }
}

void Core::_init()
{
    _prenderer->set_window(_pwindow.get());

    _prenderer->set_camera(_pcamera.get());    
    
    _pcontroller->set_input(_pinput.get());
}

void Core::_poll_events(Input& input)
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

    input.reset();

    int keys{0};
    const Uint8* kbstate = SDL_GetKeyboardState(&keys);
    
    if (kbstate[SDL_SCANCODE_UP]) {
	input.set_keystate("kUp", true);
    }

    if (kbstate[SDL_SCANCODE_DOWN]) {
	input.set_keystate("kDown", true);
    }

    if (kbstate[SDL_SCANCODE_LEFT]) {
	input.set_keystate("kLeft", true);
    }

    if (kbstate[SDL_SCANCODE_RIGHT]) {
	input.set_keystate("kRight", true);
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
