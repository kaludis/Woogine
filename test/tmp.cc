main()
{
    Core core;

    Scene scene;
    scene.add_entity();
    scene.add_entity();    
  
    Renderer renderer;
    core.set_renderer(renderer);
    
    while (core.is_running()) {
	core.run_scene(scene);
    }
}
