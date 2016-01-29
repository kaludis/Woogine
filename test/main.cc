#include "../src/entitycreator.h"
#include "../src/entity.h"
#include "../src/entityresources.h"

#include "../src/datareaderexception.h"
#include "../src/resourcemanagerexception.h"
#include "../src/entitycreatorexc.h"

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

constexpr int screen_width = 1024;
constexpr int screen_height = 768;

void print_entity(const EntityPtr& pentity)
{
    const EntityResources& res = pentity->resources();
    cout << "\nPrint entity '" << pentity->name() << "':" << endl;
    cout << "program: " << res.program.program_id << endl
	 << "attrib_coord3d: " << res.program.attrib_coord3d << endl
	 << "attrib_texcoord: " << res.program.attrib_texcoord << endl
	 << "uniform_mvp: " << res.program.uniform_mvp << endl
	 << "uniform_sampler3d: " << res.program.uniform_sampler2d << endl
	 << "buffer: " << res.mesh.buffer_id << endl
	 << "index_buffer: " << res.mesh.indexbuffer_id << endl
	 << "index count: " << res.mesh.index_count << endl
	 << "texture: " << res.texture.tex_id << endl;
}

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
	EntityCreator ecreator{};	
	ecreator.set_entity_file("../data/entities.data");
	
	EntityPtr ent1 = ecreator.create_entity("cube");
	print_entity(ent1);
	
	EntityPtr ent2 = ecreator.create_entity("triangle");
	print_entity(ent2);
	
	
    } catch (const DataReaderException& ex) {
	cout << "DataReader: " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch (const ResourceManagerException& ex) {
	cout << "ResourceManager: " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch (const EntityCreatorException& ex) {
	cout << "EntityCreator: " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch (...) {
	cout << "Unknown exception" << endl;
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
