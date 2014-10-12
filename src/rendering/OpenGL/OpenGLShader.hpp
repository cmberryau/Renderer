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
#include "rendering/OpenGL/OpenGLCommon.hpp"

namespace Renderer
{
    class OpenGLShader : public Shader
    {
        public:			
			explicit OpenGLShader();
			~OpenGLShader();

            void Compile(std::string & vertex_shader_source,
                         std::string & fragment_shader_source) override;
        
            void Compile(std::string & vertex_shader_source,
                         std::string & geometry_shader_source,
                         std::string & fragment_shader_source) override;

            void Use() override;

            GLuint Program();
        
        protected:
            GLuint _program;
    };
}

#endif // _opengl_shader_h

#endif // !EMSCRIPTEN