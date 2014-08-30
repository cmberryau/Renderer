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
    Shader * ShaderFactory::Create(char * vertex_shader_source,
                                   char * geometry_shader_source,
                                   char * fragment_shader_source,
                                   RenderingContext * context)
    {
        Shader * shader = context->Shader();
        
        shader->Compile(vertex_shader_source,
                        geometry_shader_source,
                        fragment_shader_source);
        
        return shader;
    }
    
    Shader * ShaderFactory::Create(char * vertex_shader_source,
                                   char * fragment_shader_source,
                                   RenderingContext * context)
    {
        return Create(vertex_shader_source,
                      nullptr,
                      fragment_shader_source,
                      context);
    }
}