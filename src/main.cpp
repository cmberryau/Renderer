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

#include "math/Vector.hpp"
#include "geometry/MeshFactory.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"
#include "objects/Object.hpp"
#include "scene/Scene.hpp"
#include "tests/Rotator.hpp"

#include "rendering/ShaderFactory.hpp"
#include "rendering/Material.hpp"

#include "utility/io.hpp"

using namespace Renderer;

int main(int argc, char ** argv)
{

#ifdef _WIN32
    Mesh * bunny_mesh = MeshFactory::MeshFromObjFile("assets//bunny.obj");
#else
	Mesh * bunny_mesh = MeshFactory::MeshFromObjFile("assets/bunny.obj");
#endif
    
    // window, events, graphics context and scene
	Window * window = new Window(640, 480);
	EventListener * event_listener = new EventListener();
	RenderingContext * rendering_context = new OpenGLRenderingContext(window);
	Scene * scene = new Scene();
    
    // object, mesh and meshrenderer
	Object * test_object = new Object();
	Mesh * test_mesh = new Mesh();
	MeshRenderer * test_mesh_renderer = rendering_context->MeshRenderer();
    
    // shader and material
#ifdef _WIN32
    Shader * test_shader = ShaderFactory::Create(IO::ReadFile("src//shaders//GLSL//default.vert"),
                                                 IO::ReadFile("src//shaders//GLSL//default.geom"),
                                                 IO::ReadFile("src//shaders//GLSL//default.frag"),
                                                 rendering_context);
#else
	Shader * test_shader = ShaderFactory::Create(IO::ReadFile("src/shaders/GLSL/default.vert"),
												 IO::ReadFile("src/shaders/GLSL/default.geom"),
												 IO::ReadFile("src/shaders/GLSL/default.frag"),
												 rendering_context);
#endif
    Material * test_material = new Material(test_shader);
    
    test_mesh_renderer->SetMaterial(test_material);
	scene->AddObject(test_object);

    Vector4f * test_vertices = new Vector4f[4];
    
    test_vertices[0][0] = -10.0f;
    test_vertices[0][1] = -10.0f;
    test_vertices[0][2] = 100.0f;
	test_vertices[0][3] = 1.0f;
    
    test_vertices[1][0] = -10.0f;
    test_vertices[1][1] = 10.0f;
    test_vertices[1][2] = 100.0f;
	test_vertices[1][3] = 1.0f;

    test_vertices[2][0] = 10.0f;
    test_vertices[2][1] = 10.0f;
    test_vertices[2][2] = 100.0f;
	test_vertices[2][3] = 1.0f;
    
    test_vertices[3][0] = 10.0f;
    test_vertices[3][1] = -10.0f;
    test_vertices[3][2] = 100.0f;
	test_vertices[3][3] = 1.0f;

	test_mesh->SetVertices(test_vertices, 4);
    
	Vector4f * test_colors = new Vector4f[4];

	test_colors[0][0] = 1.0f;
	test_colors[0][1] = 0.0f;
	test_colors[0][2] = 0.0f;
	test_colors[0][3] = 1.0f;

	test_colors[1][0] = 0.0f;
	test_colors[1][1] = 1.0f;
	test_colors[1][2] = 0.0f;
	test_colors[1][3] = 1.0f;

	test_colors[2][0] = 0.0f;
	test_colors[2][1] = 0.0f;
	test_colors[2][2] = 1.0f;
	test_colors[2][3] = 1.0f;

	test_colors[3][0] = 1.0f;
	test_colors[3][1] = 1.0f;
	test_colors[3][2] = 0.0f;
	test_colors[3][3] = 1.0f;

	test_mesh->SetColors(test_colors, 4);

	Vector3ui * test_triangles = new Vector3ui[2];

	test_triangles[0][0] = 0;
	test_triangles[0][1] = 1;
	test_triangles[0][2] = 2;

	test_triangles[1][0] = 2;
	test_triangles[1][1] = 3;
	test_triangles[1][2] = 0;

	test_mesh->SetTriangles(test_triangles, 2);
	
	delete test_triangles;
	delete test_colors;
    delete test_vertices;

	test_mesh_renderer->SetMesh(bunny_mesh);
    //test_mesh_renderer->SetMesh(test_mesh);
	test_object->AddMeshRenderer(test_mesh_renderer);
	test_object->LocalTransform()->SetPosition(0.0f, 0.0f, 100.0f);
	test_object->LocalTransform()->SetScale(500.0f, 500.0f, 500.0f);
    
    IObjectAddable * rotator = new Rotator();
    test_object->Add(rotator);
    
    Object * camera_object = new Object();
    Camera * camera = new Camera(rendering_context);
    camera_object->Add(camera);
    rendering_context->SetCamera(camera);
    
	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
            break;
        
		rendering_context->BeginScene();

		// Render here
        scene->UpdateAndDraw();
        
        rendering_context->EndScene();
        
		window->Swap();
	}
    
    delete test_object;
    delete rendering_context;
    delete event_listener;
    delete window;

	return 0;
}