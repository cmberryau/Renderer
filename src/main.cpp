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

    Vector3f * test_vertices = new Vector3f[3];
    
    test_vertices[0][0] = -100.0f;
    test_vertices[0][1] = -100.0f;
    test_vertices[0][2] = 10.0f;
    
    test_vertices[1][0] = -100.0f;
    test_vertices[1][1] = 100.0f;
    test_vertices[1][2] = 10.0f;
    
    test_vertices[2][0] = 100.0f;
    test_vertices[2][1] = -100.0f;
    test_vertices[2][2] = 10.0f;
    
    Mesh * test_mesh = Mesh::Create(test_vertices, 3);
    MeshRenderer * test_mesh_renderer = MeshRenderer::Create(rendering_context);
    
    Object * test_object = new Object();
    test_object->AddMesh(test_mesh);
    test_object->AddMeshRenderer(test_mesh_renderer);
    
	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
			break;
        
		// work on figuring out rendering pattern

		// Render here
        test_object->Draw();
        
		window->Swap();
	}

	return 0;
}