//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#define _RENDERER_FLOAT

#include "windowing/Window.hpp"
#include "events/EventListener.hpp"
#include "rendering/OpenGL/OpenGLRenderingContext.hpp"

#include "math/Vector.hpp"
#include "geometry/Mesh.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"
#include "objects/Object.hpp"
#include "scene/Scene.hpp"

using namespace Renderer;

int main(int argc, char ** argv)
{
	Window * window = Window::Create(640, 480);
	EventListener * event_listener = EventListener::Create();

#ifdef _RENDERER_FLOAT
	// float based test
	RenderingContext * rendering_context = OpenGLRenderingContext::Create(window);
	Object * test_object = new Object();
	Mesh * test_mesh = new Mesh();
	MeshRenderer * test_mesh_renderer = rendering_context->MeshRenderer();

	Scene * scene = Scene::Create();
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

	test_object->AddMesh(test_mesh);
	test_object->AddMeshRenderer(test_mesh_renderer);

#else 
	RenderingContextd * rendering_context = OpenGLRenderingContextd::Create(window);
	Objectd * test_object = new Objectd();
	Meshd * test_mesh = new Meshd();
	MeshRendererd * test_mesh_renderer = rendering_context->MeshRenderer();

	Scened * scene = Scened::Create();
	scene->AddObject(test_object);

	Vector4d * test_vertices = new Vector4d[4];

	test_vertices[0][0] = -10.0;
	test_vertices[0][1] = -10.0;
	test_vertices[0][2] = 100.0;
	test_vertices[0][3] = 1.0;

	test_vertices[1][0] = -10.0;
	test_vertices[1][1] = 10.0;
	test_vertices[1][2] = 100.0;
	test_vertices[1][3] = 1.0;

	test_vertices[2][0] = 10.0;
	test_vertices[2][1] = 10.0;
	test_vertices[2][2] = 100.0;
	test_vertices[2][3] = 1.0;

	test_vertices[3][0] = 10.0;
	test_vertices[3][1] = -10.0;
	test_vertices[3][2] = 100.0;
	test_vertices[3][3] = 1.0;

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

	test_object->AddMesh(test_mesh);
	test_object->AddMeshRenderer(test_mesh_renderer);
#endif

	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
            break;
        
		rendering_context->BeginScene();

		// Render here
        scene->Draw();
        
        rendering_context->EndScene();
        
		window->Swap();
	}
    
    delete test_object;
    delete rendering_context;
    delete event_listener;
    delete window;

	return 0;
}