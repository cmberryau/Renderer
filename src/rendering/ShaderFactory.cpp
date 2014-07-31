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
        if(vertex_shader_source == nullptr || fragment_shader_source == nullptr)
        {
            return nullptr;
        }
        
        const char * sources[3] = {vertex_shader_source,
                                   geometry_shader_source,
                                   fragment_shader_source};
        
        GLenum types[3] = {GL_VERTEX_SHADER,
                           GL_GEOMETRY_SHADER,
                           GL_FRAGMENT_SHADER};
        
        GLuint program = glCreateProgram();
        
        // run through the shader sources
        for(int i = 0; i < 3; i++)
        {
            if(sources[i] == nullptr)
            {
                continue;
            }
            
            // create and compile shaders
            GLuint shader = glCreateShader(types[i]);
            glShaderSource(shader, 1, &sources[i], NULL);
            glCompileShader(shader);
            
            // check compilation results
            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if(!compiled)
            {
                GLsizei log_length;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
                
                GLchar * shader_log = new GLchar[log_length + 1];
                glGetShaderInfoLog(shader, log_length, &log_length, shader_log);
                
                delete [] shader_log;
                
                return nullptr;
            }
            
            glAttachShader(program, shader);
        }
        
        return new OpenGLShader(program);
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