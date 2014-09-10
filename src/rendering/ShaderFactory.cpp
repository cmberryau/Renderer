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
    Shader * ShaderFactory::Create(std::string & vertex_shader_source,
                                   std::string & geometry_shader_source,
                                   std::string & fragment_shader_source,
                                   RenderingContext * context)
    {
        Shader * shader = context->Shader();
        
        shader->Compile(vertex_shader_source,
                        geometry_shader_source,
                        fragment_shader_source);
        
        return shader;
    }
    
    Shader * ShaderFactory::Create(std::string & vertex_shader_source,
                                   std::string & fragment_shader_source,
                                   RenderingContext * context)
    {
        std::string empty_source("");
        
        return Create(vertex_shader_source,
                      empty_source,
                      fragment_shader_source,
                      context);
    }
}