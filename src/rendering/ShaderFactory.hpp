//
//  MeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _shader_factory_h
#define _shader_factory_h

#include "OpenGL/OpenGLRenderingContext.hpp"
#include "OpenGL/OpenGLShader.hpp"

namespace Renderer
{
    class ShaderFactory
    {
        public:
            static Shader * Create(const char * vertex_shader_source,
                                   const char * geometry_shader_source,
                                   const char * fragment_shader_source,
                                   RenderingContext * context);
        
            static Shader * Create(const char * vertex_shader_source,
                                   const char * fragment_shader_source,
                                   RenderingContext * context);
        
        private:
            ~ShaderFactory(){}
            ShaderFactory(){};
    };
}

#endif // _shader_factory_h