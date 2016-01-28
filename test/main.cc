#include "../src/resourcemanager.h"

#include "../src/datareaderexception.h"
#include "../src/resourcemanagerexception.h"
#include "../src/texturedatareaderexception.h"
#include "../src/fsresolverexception.h"

#include "../src/program.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

constexpr int screen_width = 1024;
constexpr int screen_height = 768;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("My not first triangle",
					  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					  screen_width, screen_height,
					  SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    SDL_GL_CreateContext(window);

    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);

    GLenum glew_status = glewInit();

    if (glew_status != GLEW_OK) {
	cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
	return EXIT_FAILURE;
    }

    try {
	ResourceManager resman{};
	Program prog = resman.entity_program("cube");
	cout << "prog: " << prog.program_id << endl;
	
	Mesh mesh = resman.entity_mesh("cube");
	cout << "mesh.buffer: " << mesh.buffer_id << endl
	     << "mesh.indexbuffer: " << mesh.indexbuffer_id << endl
	     << "mesh.index_count: " << mesh.index_count << endl;
	
	Texture tex = resman.entity_texture("cube");
	cout << "tex: " << tex.tex_id << endl;
    } catch (const FSResolverException& ex) {
	cout<< ex.what() << endl;
    }

    return 0;
}
