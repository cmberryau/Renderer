//
//  Application.cpp
//  Renderer
//
//  Created by Christopher Berry on 12/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Application.hpp"

namespace Renderer
{
	Application::Application(std::shared_ptr<Window> window,
                             std::shared_ptr<RenderingContext> rendering_context,
                             std::shared_ptr<EventListener> event_listener) :
                             _window(window),
                             _event_listener(event_listener),
                             _rendering_context(rendering_context)				
	{

	}

	Application::~Application()
	{
		SDL_Quit();
	}

	void Application::Start()
	{
        std::unique_ptr<Scene> scene(new Scene());
        _scene = std::move(scene);
        
        std::unique_ptr<Object> camera_object(new Object());
        Camera * camera_raw = new Camera(75.0f, 1.33f, 1.0f, 500.0f);
        std::unique_ptr<ObjectAddable> camera(camera_raw);
        _scene->SetMainCamera(camera_raw);
        _scene->AddObject(camera_object);

#ifdef EMSCRIPTEN
        std::string cube_file_path("cube.obj");
#else
        std::string cube_file_path("assets/cube.obj");
#endif
        std::shared_ptr<Mesh> cube_mesh = MeshFactory::MeshFromObjFile(cube_file_path);
        
#ifdef EMSCRIPTEN
        std::string vertex_shader_path("/shaders/GLSL/default.vert");
        std::string fragment_shader_path("/shaders/GLSL/default.frag");
#else
        std::string vertex_shader_path("src/shaders/GLSL/default.vert");
        std::string fragment_shader_path("src/shaders/GLSL/default.frag");
#endif
        
        std::string vertex_shader_source = IO::ReadFile(vertex_shader_path);
        std::string fragment_shader_source = IO::ReadFile(fragment_shader_path);
        
        std::shared_ptr<Shader> default_shader = ShaderFactory::Create(vertex_shader_source, fragment_shader_source);
        std::shared_ptr<Material> default_material(new Material(default_shader));
        
        std::unique_ptr<Object> cube_object(new Object());
#ifdef EMSCRIPTEN
        MeshRenderer * cube_mesh_renderer_raw = new OpenGLESMeshRenderer();
#else
        MeshRenderer * cube_mesh_renderer_raw = new OpenGLMeshRenderer();
#endif
        std::unique_ptr<MeshRenderer> cube_mesh_renderer(cube_mesh_renderer_raw);
        cube_mesh_renderer->AddMaterial(default_material);
        cube_mesh_renderer->AddMesh(cube_mesh);
        cube_object->LocalTransform().SetPosition(0.0f, 0.0f, 4.0f);
        cube_object->AddMeshRenderer(cube_mesh_renderer);
        
        std::unique_ptr<ObjectAddable> spinner(new Spinner());
        cube_object->Add(spinner);
        
        _scene->AddObject(cube_object);
        
		while (true)
		{
			MainLoop();
		}
	}
    
	void Application::MainLoop()
	{
		_event_listener->ListenForEvents();

		if (_event_listener->ShouldQuit())
		{
			End();
		}

		_rendering_context->BeginScene();

		_scene->UpdateAndDraw();

		_rendering_context->EndScene();

		_window->Swap();
	}

    void Application::End()
    {
        _scene.reset();
        
        exit(0);
    }

    Scene & Application::GetScene()
    {
        return *_scene;
    }
    
    Window & Application::GetWindow()
    {
        return *_window;
    }
    
	EventListener & Application::GetEventListener()
	{
		return *_event_listener;
	}

	RenderingContext & Application::GetRenderingContext()
	{
		return *_rendering_context;
	}
    
    void Application::SetScene(std::unique_ptr<Scene> & scene)
    {
        _scene = std::move(scene);
    }
}