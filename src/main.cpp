//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef _WINDOWS
    #include <windows.h>
#endif

#include <iostream>

#define GL_GLEXT_PROTOTYPES 1

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    
    glFlush();
}

int main(int argc, const char * argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stdout, "SDL_Init failed!");
        return -1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_Window * window = SDL_CreateWindow("Renderer",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           640, 480,
                                           SDL_WINDOW_OPENGL);
    
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    
    if(gl_context == NULL)
    {
        fprintf(stdout, "SDL_GL_CreateContext failed!");
    }
    
    GLint major_version = -1;
    GLint minor_version = -1;
    
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    
    fprintf(stdout, "OpenGL version: %d.%d", major_version, minor_version);
    
    SDL_Event event;
    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                break;
            }
            
            render();
        }
        
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}