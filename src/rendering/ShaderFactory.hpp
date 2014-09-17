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

#include "OpenGLES/OpenGLESRenderingContext.hpp"
#include "OpenGLES/OpenGLESShader.hpp"

#include <string>

namespace Renderer
{
    class ShaderFactory
    {
        public:
            static Shader * Create(std::string & vertex_shader_source,
                                   std::string & geometry_shader_source,
                                   std::string & fragment_shader_source,
                                   RenderingContext * context);
        
            static Shader * Create(std::string & vertex_shader_source,
                                   std::string & fragment_shader_source,
                                   RenderingContext * context);
        
        private:
            ~ShaderFactory(){}
            ShaderFactory(){};
    };
}

#endif // _shader_factory_h