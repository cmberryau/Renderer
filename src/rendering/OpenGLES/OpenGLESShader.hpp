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
#include "rendering/OpenGLES/OpenGLESCommon.hpp"

namespace Renderer
{
    class OpenGLESShader : public Shader
    {
        public:
            explicit OpenGLESShader();
            ~OpenGLESShader();
        
        
            void Compile(std::string & vertex_shader_source,
                         std::string & fragment_shader_source) override;
            
            void Compile(std::string & vertex_shader_source,
                         std::string & geometry_shader_source,
                         std::string & fragment_shader_source) override;
        
            void Use() override;
            
            const GLuint Program() const;
        
        private:
            GLuint _program;
    };
}

#endif // _opengles_shader_h

#endif