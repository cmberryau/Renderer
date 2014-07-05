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

#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>

#include "utility\LoadShaders.h"
#include "math\Matrix.h"

#include "geometry\Mesh.h"
#include "objects\Object.h"
#include "rendering\RenderingContext.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

using namespace Renderer;

GLuint vertex_array_objects[1];
GLuint element_array_objects[1];

const GLuint num_verts = 3;

void InitGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GLuint program;
GLint model_matrix_uniform;
GLint projection_matrix_uniform;

void CreateTestVAO()
{
    GLuint vertex_buffers[1];
    
    GLfloat vertices[4][4] =
    {
        { -10.00, -10.00, 50.0, 1.0 },
		{ 10.00, -10.0, 50.0, 1.0 },
		{ -10.00, 10.0, 50.0, 1.0 },
        { -10.00, -10.00, 50.0, 1.0 },
    };
    
    GLfloat colors[4][4] =
    {
        {1.0, 0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0, 1.0},
    };
    
    static const GLushort vertex_indices[] =
    {
        0, 1, 2
    };
    
    glGenBuffers(1, element_array_objects);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array_objects[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, vertex_array_objects);
    glBindVertexArray(vertex_array_objects[0]);
    glGenBuffers(1, vertex_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    
    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "src\\shaders\\triangles.vert" },
        { GL_FRAGMENT_SHADER, "src\\shaders\\triangles.frag" },
        { GL_NONE, NULL }
    };
    
    program = LoadShaders(shaders);
    
    glUseProgram(program);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) sizeof(vertices));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
	model_matrix_uniform = glGetUniformLocation(program, "model_matrix");
	projection_matrix_uniform = glGetUniformLocation(program, "projection_matrix");
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vertex_array_objects[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array_objects[0]);
    
   	Matrix4f model_matrix = Matrix4f::Translate(-36.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, num_verts);

   	model_matrix = Matrix4f::Translate(-12.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
    
   	model_matrix = Matrix4f::Translate(12.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, model_matrix);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

   	model_matrix = Matrix4f::Translate(36.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, model_matrix);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
    
    glFlush();
}

int main(int argc, char ** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stdout, "SDL_Init failed!\n");
		return -1;
	}

	RenderingContext * test_rendering_context = new RenderingContext();

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
    
	//Matrix4f projection_matrix = Matrix4f::Orthographic(0.0f, 640.0f, 0.0f, 480.0f, 1.0f, 500.0f);
	Matrix4f projection_matrix = Matrix4f::Perspective(75.0f, 1.33f, 1.0f, 500.0f);

    glUseProgram(program);
	glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, projection_matrix);
    
    SDL_Event event;
    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                break;
            }
                               
            Render();
        }
        
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}