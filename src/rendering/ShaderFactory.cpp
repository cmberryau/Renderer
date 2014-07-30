//
//  ShaderFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ShaderFactory.hpp"

namespace Renderer
{
    Shader * ShaderFactory::Create(const char * vertex_shader_source,
                                   const char * geometry_shader_source,
                                   const char * fragment_shader_source,
                                   OpenGLRenderingContext * context)
    {
        
        
        return nullptr;
    }
    
    Shader * ShaderFactory::Create(const char * vertex_shader_source,
                                   const char * fragment_shader_source,
                                   OpenGLRenderingContext * context)
    {
        return Create(vertex_shader_source,
                      nullptr,
                      fragment_shader_source,
                      context);
    }
}