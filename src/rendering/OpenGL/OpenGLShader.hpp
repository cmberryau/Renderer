//
//  OpenGLShader.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#ifndef _opengl_shader_h
#define _opengl_shader_h

#include "rendering/Shader.hpp"

// OpenGL includes
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#ifdef EMSCRIPTEN
#include <SDL/SDL_opengl.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

namespace Renderer
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader * Compile(std::string & vertex_shader_source,
                                   std::string & fragment_shader_source);
        
            OpenGLShader * Compile(std::string & vertex_shader_source,
                                   std::string & geometry_shader_source,
                                   std::string & fragment_shader_source);
            void Use();
            GLuint Program();
        
            ~OpenGLShader();
            OpenGLShader();
        
        protected:
            GLuint _program;
    };
}

#endif // _opengl_shader_h

#endif // !EMSCRIPTEN