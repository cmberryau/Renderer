//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
	#include <gl\glew.h>
#else
	#define GL_GLEXT_PROTOTYPES 1
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "utility/LoadShaders.h"
#include "math/Matrix.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint vertex_array_objects[1];
const GLuint num_verts = 3;

void InitGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GLint model_matrix_uniform;

void CreateTestVAO()
{
    GLuint vertex_buffers[1];
    
    glGenVertexArrays(1, vertex_array_objects);
    glBindVertexArray(vertex_array_objects[0]);
    
    GLfloat vertices[3][2] = {
        { -0.90, -0.90 },
        { 0.85, -0.90 },
        { -0.90, 0.85 }
    };
    
    glGenBuffers(1, vertex_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "src\\shaders\\triangles.vert" },
        { GL_FRAGMENT_SHADER, "src\\shaders\\triangles.frag" },
        { GL_NONE, NULL }
    };
    
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    glVertexAttribPointer(0, 2, GL_FLOAT,
                          GL_FALSE, 0, BUFFER_OFFSET(0));

	glGetUniformLocation(program, "model_matrix");

    glEnableVertexAttribArray(0);
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vertex_array_objects[0]);
    glDrawArrays(GL_TRIANGLES, 0, num_verts);
    
    glFlush();
}

using namespace Renderer;

int main(int argc, char ** argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stdout, "SDL_Init failed!\n");
        return -1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_Window * window = SDL_CreateWindow("Renderer",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           640, 480,
                                           SDL_WINDOW_OPENGL);
    
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    
    if(gl_context == NULL)
    {
        fprintf(stdout, "SDL_GL_CreateContext failed!\n");
    }
 
#ifdef _WIN32
    
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stdout, "glewInit failed!\n");
		return -1;
	}
    
#endif

    GLint major_version = -1;
    GLint minor_version = -1;
    
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    
    fprintf(stdout, "OpenGL version: %d.%d\n", major_version, minor_version);
    
    InitGL();
    CreateTestVAO();
    
	Matrix4f projection_matrix = Matrix4f::identity();
	projection_matrix.Print();

    SDL_Event event;
    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                break;
            }

			glUniformMatrix4fv(model_matrix_uniform, 4, GL_FALSE, projection_matrix);
                               
            Render();
        }
        
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}