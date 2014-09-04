//
//  OpenGLESShader.cpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLESShader.hpp"
#include <stdio.h>
#include <memory>
#include <exception>

namespace Renderer
{
    OpenGLESShader * OpenGLESShader::Compile(char * vertex_shader_source,
                                             char * fragment_shader_source)
	{
        
        return this;
    }
    
    OpenGLESShader * OpenGLESShader::Compile(char * vertex_shader_source,
                                             char * geometry_shader_source,
                                             char * fragment_shader_source)
	{
        return this->Compile(vertex_shader_source, fragment_shader_source);
    }
    
    void OpenGLESShader::Use()
    {

    }
    
    GLuint OpenGLESShader::Program()
    {
        return _program;
    }
    
    OpenGLESShader::~OpenGLESShader()
    {
        
    }
    
    OpenGLESShader::OpenGLESShader()
    {
        
    }
}
