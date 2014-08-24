//
//  OpenGLShader.cpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLShader.hpp"
#include <stdio.h>

namespace Renderer
{
    OpenGLShader * OpenGLShader::Compile(const char * vertex_shader_source,
                                         const char * geometry_shader_source,
                                         const char * fragment_shader_source)
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
        
        GLuint shaders[3];
        
		_program = glCreateProgram();
        
        // run through the shader sources
        for(int i = 0; i < 3; i++)
        {
            if(sources[i] == nullptr)
            {
                shaders[i] = -1;
                continue;
            }
            
            // create and compile shaders
            shaders[i] = glCreateShader(types[i]);
            glShaderSource(shaders[i], 1, &sources[i], nullptr);
            glCompileShader(shaders[i]);
            
            // check compilation results
            GLint compiled;
            glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &compiled);
            if(!compiled)
            {
                GLsizei log_length;
                glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &log_length);
                
                GLchar * shader_log = new GLchar[log_length + 1];
                glGetShaderInfoLog(shaders[i], log_length, &log_length, shader_log);
                
                printf("%s", shader_log);
                
                delete [] shader_log;
                
                return nullptr;
            }
            
            glAttachShader(_program, shaders[i]);
        }
        
        glLinkProgram(_program);
        
        GLint linked;
        glGetProgramiv(_program, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            GLsizei log_length;
            glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &log_length);
            
            GLchar * shader_log = new GLchar[log_length + 1];
            glGetShaderInfoLog(_program, log_length, &log_length, shader_log);
            
            printf("%s", shader_log);
            
            delete [] shader_log;
            
            for(int i = 0; i < 3; i++)
            {
                if(shaders[i] != -1)
                {
                    glDeleteShader(shaders[i]);
                }
            }
            
            return nullptr;
        }
        
        GLenum error;
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            fprintf(stderr, "%d\n", error);
        }

        return this;
    }
    
    void OpenGLShader::Use()
    {
        glUseProgram(_program);
        
        GLenum error;
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            fprintf(stderr, "%d\n", error);
        }
    }
    
    GLuint OpenGLShader::Program()
    {
        return _program;
    }
    
    OpenGLShader::~OpenGLShader()
    {
        
    }
    
    OpenGLShader::OpenGLShader()
    {
        
    }
}