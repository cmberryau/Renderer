//
//  OpenGLShader.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_shader_h
#define _opengl_shader_h

#include "rendering/Shader.hpp"

// OpenGL includes
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <SDL2/SDL_opengl.h>

namespace Renderer
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader * Compile(const char * vertex_shader_source,
                                   const char * geometry_shader_source,
                                   const char * fragment_shader_source);
            void Use();
            GLuint Program();
        
            ~OpenGLShader();
            OpenGLShader();
        
        protected:
            GLuint _program;
    };
}

#endif // _opengl_shader_h