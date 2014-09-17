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
#include "rendering/OpenGLES/OpenGLESRenderingContext.hpp"

#include "geometry/MeshFactory.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"
#include "objects/Object.hpp"
#include "scene/Scene.hpp"

#include "rendering/ShaderFactory.hpp"
#include "rendering/Material.hpp"

#include "tests/Rotator.hpp"

#include "utility/io.hpp"

// for memory leak detection on windows
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef EMSCRIPTEN 
#include <emscripten.h>
#endif

using namespace Renderer;

Window window(640, 480);
EventListener * event_listener;
RenderingContext * rendering_context;
Scene * scene;

void emscripten_loop()
{
	event_listener->ListenForEvents();

	if (event_listener->ShouldQuit())
	{
		return;
	}

	rendering_context->BeginScene();

	// Render here
	scene->UpdateAndDraw();

	rendering_context->EndScene();

	window.Swap();
}

void entry()
{
	event_listener = new EventListener();

#ifndef EMSCRIPTEN
	rendering_context = new OpenGLRenderingContext(&window);
#else
	rendering_context = new OpenGLESRenderingContext(&window);
#endif

	scene = new Scene();

	std::string sphere_file;
	std::string cube_file;
	std::string cone_file;
	std::string bunny_file;

#ifdef _WIN32
	sphere_file = std::string("assets//sphere.obj");
	cube_file = std::string("assets//cube.obj");
	cone_file = std::string("assets//cone.obj");
	bunny_file = std::string("assets//bunny.obj");
#elif EMSCRIPTEN
	sphere_file = std::string("sphere.obj");
	cube_file = std::string("cube.obj");
	cone_file = std::string("cone.obj");
	bunny_file = std::string("bunny.obj");
#else
	sphere_file = std::string("assets/sphere.obj");
	cube_file = std::string("assets/cube.obj");
	cone_file = std::string("assets/cone.obj");
	bunny_file = std::string("assets/bunny.obj");
#endif

	Mesh * sphere_mesh = MeshFactory::MeshFromObjFile(sphere_file);
	Mesh * cube_mesh = MeshFactory::MeshFromObjFile(cube_file);
	Mesh * cone_mesh = MeshFactory::MeshFromObjFile(cone_file);
	Mesh * bunny_mesh = MeshFactory::MeshFromObjFile(bunny_file);

	std::string vertex_source_file;
	std::string fragment_source_file;

#ifdef _WIN32
	vertex_source_file = std::string("src//shaders//GLSL//default.vert");
	fragment_source_file = std::string("src//shaders//GLSL//default.frag");
#elif EMSCRIPTEN
	vertex_source_file = std::string("/shaders/GLSLES/default.vert");
	fragment_source_file = std::string("/shaders/GLSLES/default.frag");
#else
	vertex_source_file = std::string("src/shaders/GLSL/default.vert");
	fragment_source_file = std::string("src/shaders/GLSL/default.frag");
#endif
	std::string vertex_source;
	std::string fragment_source;

	vertex_source = IO::ReadFile(vertex_source_file);
	fragment_source = IO::ReadFile(fragment_source_file);

	Shader * test_shader = ShaderFactory::Create(vertex_source, fragment_source, rendering_context);

	Object * sphere_object = new Object();
	MeshRenderer * sphere_mesh_renderer = rendering_context->MeshRenderer();
	Material * sphere_material = new Material(test_shader);

	sphere_mesh_renderer->SetMaterial(sphere_material);
	sphere_mesh_renderer->SetMesh(sphere_mesh);
	sphere_object->AddMeshRenderer(sphere_mesh_renderer);

	scene->AddObject(sphere_object);
	sphere_object->LocalTransform()->SetPosition(0.0f, 0.0f, 4.0f);

	Object * cone_object = new Object();
	MeshRenderer * cone_mesh_renderer = rendering_context->MeshRenderer();
	Material * cone_material = new Material(test_shader);

	cone_mesh_renderer->SetMaterial(cone_material);
	cone_mesh_renderer->SetMesh(cone_mesh);
	cone_object->AddMeshRenderer(cone_mesh_renderer);

	scene->AddObject(cone_object);
	cone_object->LocalTransform()->SetPosition(-2.0f, 0.0f, 4.0f);

	Object * cube_object = new Object();
	MeshRenderer * cube_mesh_renderer = rendering_context->MeshRenderer();
	Material * cube_material = new Material(test_shader);

	cube_mesh_renderer->SetMaterial(cube_material);
	cube_mesh_renderer->SetMesh(cube_mesh);
	cube_object->AddMeshRenderer(cube_mesh_renderer);

	scene->AddObject(cube_object);
	cube_object->LocalTransform()->SetPosition(2.0f, 0.0f, 4.0f);

	Object * bunny_object = new Object();
	MeshRenderer * bunny_mesh_renderer = rendering_context->MeshRenderer();
	Material * bunny_material = new Material(test_shader);

	bunny_mesh_renderer->SetMaterial(bunny_material);
	bunny_mesh_renderer->SetMesh(bunny_mesh);
	bunny_object->AddMeshRenderer(bunny_mesh_renderer);

	scene->AddObject(bunny_object);
	bunny_object->LocalTransform()->SetPosition(0.0f, -2.0f, 3.0f);
	bunny_object->LocalTransform()->SetScale(10.0f, 10.0f, 10.0f);

	Object * camera_object = new Object();
	Camera * camera = new Camera(rendering_context);
	camera_object->Add(camera);
	scene->AddObject(camera_object);

	rendering_context->SetCamera(camera);
	

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(emscripten_loop, 0, true);
#endif

	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
		{
			break;
		}

		rendering_context->BeginScene();

		// Render here
		scene->UpdateAndDraw();

		rendering_context->EndScene();

		window.Swap();
	}	

	delete bunny_material;
	delete bunny_mesh_renderer;
	delete bunny_object;
	delete bunny_mesh;

	delete cone_material;
	delete cone_mesh_renderer;
	delete cone_object;
	delete cone_mesh;

	delete cube_material;
	delete cube_mesh_renderer;
	delete cube_object;
	delete cube_mesh;

	delete sphere_material;
	delete sphere_mesh_renderer;
	delete sphere_object;
	delete sphere_mesh;
	
	delete test_shader;
	delete camera_object;
	
	delete scene;
	delete rendering_context;
	delete event_listener;
}

int main(int argc, char ** argv)
{   
	entry();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}