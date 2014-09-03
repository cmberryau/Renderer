//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "windowing/Window.hpp"
#include "events/EventListener.hpp"
#include "rendering/OpenGL/OpenGLRenderingContext.hpp"

#include "geometry/MeshFactory.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"
#include "objects/Object.hpp"
#include "scene/Scene.hpp"

#include "rendering/ShaderFactory.hpp"
#include "rendering/Material.hpp"

#include "utility/io.hpp"

// for memory leak detection
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace Renderer;

int main(int argc, char ** argv)
{
	Window * window = new Window(640, 480);
	EventListener * event_listener = new EventListener();
	RenderingContext * rendering_context = new OpenGLRenderingContext(window);
	Scene * scene = new Scene();

	Object * test_object = new Object();
	MeshRenderer * test_mesh_renderer = rendering_context->MeshRenderer();

#ifdef _WIN32
	Mesh * test_mesh = MeshFactory::MeshFromObjFile("assets//bunny.obj");
#else
	Mesh * test_mesh = MeshFactory::MeshFromObjFile("assets/cube.obj");
#endif	

#ifdef _WIN32
	Shader * test_shader = ShaderFactory::Create(IO::ReadFile("src//shaders//GLSL//default.vert"),
		//IO::ReadFile("src//shaders//GLSL//default.geom"),
		IO::ReadFile("src//shaders//GLSL//default.frag"),
		rendering_context);
#else
	Shader * test_shader = ShaderFactory::Create(IO::ReadFile("src/shaders/GLSL/default.vert"),
		//IO::ReadFile("src/shaders/GLSL/default.geom"),
		IO::ReadFile("src/shaders/GLSL/default.frag"),
		rendering_context);
#endif
	Material * test_material = new Material(test_shader);

	test_mesh_renderer->SetMaterial(test_material);
	test_mesh_renderer->SetMesh(test_mesh);
	test_object->AddMeshRenderer(test_mesh_renderer);

	Object * camera_object = new Object();
	Camera * camera = new Camera(rendering_context);
	camera_object->Add(camera);
	rendering_context->SetCamera(camera);

	scene->AddObject(test_object);
	test_object->LocalTransform()->SetPosition(0.0f, -15.0f, 30.0f);
	test_object->LocalTransform()->SetScale(150.0f, 150.0f, 150.0f);

	scene->AddObject(camera_object);
	camera_object->LocalTransform()->SetPosition(0.0f, 0.0f, 0.0f);
	camera_object->LocalTransform()->SetRotation(0.0f, 0.0f, 0.0f);

	float rotation = 0.0f;

	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
		{
			break;
		}

		rendering_context->BeginScene();

		rotation += 1.0f;

		camera_object->LocalTransform()->SetRotation(0.0f, rotation, 0.0f);

		// Render here
		scene->UpdateAndDraw();

		rendering_context->EndScene();

		window->Swap();
	}

	//delete camera; - deleted by object
	delete camera_object;
	delete test_material;
	delete test_shader;
	delete test_mesh;
	//delete test_mesh_renderer; - deleted by object
	delete test_object;
	delete scene;
	delete rendering_context;
	delete event_listener;
	delete window;

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}