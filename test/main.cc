#include "../src/entitycreator.h"
#include "../src/entity/entity.h"
#include "../src/resources/entityresources.h"
#include "../src/text/text.h"

#include "../src/exceptions/datareaderexception.h"
#include "../src/exceptions/resourcemanagerexception.h"
#include "../src/exceptions/entitycreatorexc.h"

#include "../src/core.h"
#include "../src/window/abstractwindow.h"
#include "../src/window/window.h"
#include "../src/renderer/abstractrenderer.h"
#include "../src/renderer/renderer.h"
#include "../src/camera/abstractcamera.h"
#include "../src/camera/camera.h"
#include "../src/input/input.h"
#include "../src/controller/abstractcontroller.h"
#include "../src/controller/controller.h"
#include "../src/scene.h"
#include "../src/entity/abstractvisualentity.h"

#include "../src/debug/debug.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    //cout << "size of Entity: " << sizeof(Entity) << endl;
    
    try {
	Core core{};
	core.set_window(IWindowPtr{new Window{}});
	core.set_renderer(IRendererPtr{new Renderer{}});
	core.set_camera(ICameraPtr{new Camera{}});
	core.set_input(InputPtr{new Input{}});
	core.set_controller(IControllerPtr{new Controller{}});
	
	EntityCreator ecreator{};
	ecreator.set_entities_file("../data/entities.dat");

	ScenePtr scene{new Scene{}};

	//scene->add_entity(ecreator.create_entity("object1", "quad"));
	//DEBUG_PRINT("New entity: %s\n", ecreator.create_entity("runmen", "runmen")->name().c_str());
	scene->add_entity(ecreator.create_entity("background", "background", false));

	scene->add_entity(ecreator.create_entity("runmen", "runmen", true));

	scene->add_text("fps", ecreator.create_text("fps_text", "0 fps",
						    Point2f{5.0f, 5.0f}, 0.8f));

	const Scene::EntityPtrList& list = scene->entity_list();
	for (const IVisualEntityPtr& entity : list) {
	    std::cout << entity->name() << std::endl;
	}

	core.show_fps(true);
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
