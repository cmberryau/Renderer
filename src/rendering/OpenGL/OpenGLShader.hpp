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

#include <SDL2/SDL_opengl.h>

namespace Renderer
{
    class OpenGLShader : public Shader
    {
        public:
            void Use();
        
            virtual ~OpenGLShader(){}
            OpenGLShader(GLuint program);
        
        protected:
            GLuint _program;
    };
}

#endif // _opengl_shader_h