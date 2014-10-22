//
//  EmscriptenApplication.cpp
//  Renderer
//
//  Created by Christopher Berry on 13/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "application/EmscriptenApplication.hpp"

namespace Renderer
{
	void EmscriptenLoop()
	{
		EmscriptenApplication::Instance().GetEventListener().ListenForEvents();

		if(EmscriptenApplication::Instance().GetEventListener().ShouldQuit())
		{
			EmscriptenApplication::Instance().End();
		}

		EmscriptenApplication::Instance().GetRenderingContext().BeginScene();

        EmscriptenApplication::Instance().GetScene().UpdateAndDraw();
        
		EmscriptenApplication::Instance().GetRenderingContext().EndScene();

		EmscriptenApplication::Instance().GetWindow().Swap();
	}

	EmscriptenApplication * EmscriptenApplication::_instance = nullptr;

	EmscriptenApplication::EmscriptenApplication(std::shared_ptr<Window> window,
												 std::shared_ptr<RenderingContext> rendering_context,
												 std::shared_ptr<EventListener> event_listener) :
												 Application(window, rendering_context, event_listener)
	{
        EmscriptenApplication::_instance = this;
	}

	void EmscriptenApplication::Start()
	{
        std::unique_ptr<Scene> scene(new Scene());
        SetScene(scene);
        
        std::unique_ptr<Object> camera_object(new Object());
        Camera * camera_raw = new Camera(75.0f, 1.33f, 1.0f, 500.0f);
        std::unique_ptr<ObjectAddable> camera(camera_raw);
        GetScene().SetMainCamera(camera_raw);
        GetScene().AddObject(camera_object);
        
        std::string cube_file_path("assets/cube.obj");
        std::shared_ptr<Mesh> cube_mesh = MeshFactory::MeshFromObjFile(cube_file_path);
        
#ifdef EMSCRIPTEN
        std::string vertex_shader_path("src/shaders/GLSLES/defaultes.vert");
        std::string fragment_shader_path("src/shaders/GLSLES/defaultes.frag");
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
        
        GetScene().AddObject(cube_object);
        
		emscripten_set_main_loop(EmscriptenLoop, 0, true);
	}

	EmscriptenApplication & EmscriptenApplication::Instance()
	{        
		return *_instance;
	}
}

#endif