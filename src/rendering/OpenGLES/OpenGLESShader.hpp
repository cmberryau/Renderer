//
//  OpenGLESShader.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#ifndef _opengles_shader_h
#define _opengles_shader_h

#include "rendering/Shader.hpp"

// glew is needed on windows for shader compilation
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <SDL2/SDL_opengles2.h>

namespace Renderer
{
    class OpenGLESShader : public Shader
    {
        public:
            OpenGLESShader * Compile(std::string & vertex_shader_source,
                                     std::string & fragment_shader_source);
        
            OpenGLESShader * Compile(std::string & vertex_shader_source,
                                     std::string & geometry_shader_source,
                                     std::string & fragment_shader_source);
            void Use();
            GLuint Program();
        
            ~OpenGLESShader();
            OpenGLESShader();
        
        protected:
            GLuint _program;
    };
}

#endif // _opengles_shader_h

#endif