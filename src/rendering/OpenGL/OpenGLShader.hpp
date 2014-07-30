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

namespace Renderer
{
    class OpenGLShader
    {
        public:
            void Use();
        
            virtual ~OpenGLShader(){}
            OpenGLShader(const char * vertex_source,
                         const char * geometry_source,
                         const char * fragment_source);
        
        protected:
            const char * _vertex_source;
            const char * _geometry_source;
            const char * _fragment_source;
    };
}

#endif // _opengl_shader_h