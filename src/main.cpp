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
#include "tests/Rotator.hpp"

#include "rendering/ShaderFactory.hpp"
#include "rendering/Material.hpp"

using namespace Renderer;

static const char * read_file( const char * filename )
{
#ifdef WIN32
	FILE* infile;
	fopen_s( &infile, filename, "rb" );
#else
    FILE* infile = fopen( filename, "rb" );
#endif // WIN32
    
    if ( !infile ) {
#ifdef _DEBUG
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
        return NULL;
    }
    
    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );
    
    GLchar* source = new GLchar[len+1];
    
    fread( source, 1, len, infile );
    fclose( infile );
    
    source[len] = 0;
    
    return const_cast<const char *>(source);
}

int main(int argc, char ** argv)
{
	Window * window = Window::Create(640, 480);
	EventListener * event_listener = EventListener::Create();
    
#ifdef _RENDERER_FLOAT
	// float test
	RenderingContext * rendering_context = OpenGLRenderingContext::Create(window);
	Object * test_object = new Object();
    
	Mesh * test_mesh = new Mesh();
	MeshRenderer * test_mesh_renderer = rendering_context->MeshRenderer();
    Shader * test_shader = ShaderFactory::Create(read_file("src/shaders/GLSL/default.vert"),
                                                 read_file("src/shaders/GLSL/default.geom"),
                                                 read_file("src/shaders/GLSL/default.frag"),
                                                 rendering_context);
	
    Material * test_material = new Material(test_shader);
    test_mesh_renderer->SetMaterial(test_material);
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
    
    test_mesh_renderer->SetMesh(test_mesh);
	test_object->AddMeshRenderer(test_mesh_renderer);
    
    IObjectAddable * rotator = new Rotator();
    test_object->Add(rotator);
    
    Object * camera_object = new Object();
    Camera * camera = new Camera();
    camera_object->Add(camera);

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