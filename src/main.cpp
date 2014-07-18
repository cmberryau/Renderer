//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "windowing/Window.h"
#include "events/EventListener.h"
#include "rendering/RenderingContext.h"

#include "math/Vector.h"
#include "geometry/Mesh.h"
#include "rendering/MeshRenderer.h"
#include "objects/Object.h"

using namespace Renderer;

int main(int argc, char ** argv)
{
	Window * window = Window::Create(640, 480);
	EventListener * event_listener = EventListener::Create();
	RenderingContext * rendering_context = RenderingContext::Create(window, OpenGLContextType);

    Vector3f * test_vertices = new Vector3f[4];
    
    test_vertices[0][0] = -10.0f;
    test_vertices[0][1] = -10.0f;
    test_vertices[0][2] = 100.0f;
    
    test_vertices[1][0] = -10.0f;
    test_vertices[1][1] = 10.0f;
    test_vertices[1][2] = 100.0f;

    test_vertices[2][0] = 10.0f;
    test_vertices[2][1] = 10.0f;
    test_vertices[2][2] = 100.0f;
    
    test_vertices[3][0] = 10.0f;
    test_vertices[3][1] = -10.0f;
    test_vertices[3][2] = 100.0f;
    
    Mesh * test_mesh = Mesh::Create(test_vertices, 4);
    
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
    delete test_vertices;
    
    MeshRenderer * test_mesh_renderer = MeshRenderer::Create(rendering_context);
    
    Object * test_object = new Object();
    test_object->AddMesh(test_mesh);
    test_object->AddMeshRenderer(test_mesh_renderer);
    
    
	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
            break;
        
		rendering_context->BeginScene();

		// Render here
        test_object->Draw();
        
        rendering_context->EndScene();
        
		window->Swap();
	}
    
    delete test_object;
    delete rendering_context;
    delete event_listener;
    delete window;

	return 0;
}