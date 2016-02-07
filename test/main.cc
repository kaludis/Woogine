#include "../src/entitycreator.h"
#include "../src/entity.h"
#include "../src/entityresources.h"

#include "../src/datareaderexception.h"
#include "../src/resourcemanagerexception.h"
#include "../src/entitycreatorexc.h"

#include "../src/core.h"
#include "../src/window.h"
#include "../src/renderer.h"
#include "../src/scene.h"
#include "../src/camera.h"

#include "../src/debug.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void print_entity(const EntityPtr& pentity)
{
    const EntityResources& res = pentity->resources();
    cout << "\nPrint entity '" << pentity->name() << "':" << endl;
    cout << "program: " << res.program.program_id << endl
	 << "attrib_coord3d: " << res.program.attrib_coord3d << endl
	 << "attrib_texcoord: " << res.program.attrib_texcoord << endl
	 << "uniform_projection: " << res.program.uniform_projection << endl
	 << "uniform_view: " << res.program.uniform_view << endl
	 << "uniform_model: " << res.program.uniform_model << endl	
	 << "uniform_sampler3d: " << res.program.uniform_sampler2d << endl
	 << "buffer: " << res.mesh.buffer_id << endl
	 << "index_buffer: " << res.mesh.indexbuffer_id << endl
	 << "index count: " << res.mesh.index_count << endl
	 << "texture: " << res.texture.tex_id << endl;
}

int main()
{
    cout << "size of Entity: " << sizeof(Entity) << endl;
    
    try {
	Core core{};
	core.set_window(WindowPtr{new Window{}});
	core.set_renderer(RendererPtr{new Renderer{}});
	core.set_camera(CameraPtr{new Camera{}});
	
	EntityCreator ecreator{};
	ecreator.set_entities_file("../data/entities.data");

	ScenePtr scene{new Scene{}};

	scene->add_entity(ecreator.create_entity("quad"));

	while (core.is_running()) {
	    core.run_scene(scene);
	}
	
    } catch (const DataReaderException& ex) {
	cout << "DataReader: " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch (const ResourceManagerException& ex) {
	cout << "ResourceManager: " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch (const EntityCreatorException& ex) {
	cout << "EntityCreator: " << ex.what() << endl;
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
