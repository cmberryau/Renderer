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
	std::shared_ptr<Shader> ShaderFactory::Create(std::string & vertex_shader_source,
                                   std::string & geometry_shader_source,
                                   std::string & fragment_shader_source)
    {
#ifndef EMSCRIPTEN
		std::shared_ptr<Shader> shader(new OpenGLShader());
#else
        std::shared_ptr<Shader> shader(new OpenGLESShader());
#endif
        
        shader->Compile(vertex_shader_source,
                        geometry_shader_source,
                        fragment_shader_source);
        
        return shader;
    }
    
	std::shared_ptr<Shader> ShaderFactory::Create(std::string & vertex_shader_source,
                                   std::string & fragment_shader_source)
    {
        std::string empty_source("");
        
        return Create(vertex_shader_source,
                      empty_source,
                      fragment_shader_source);
    }
}