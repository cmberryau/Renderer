//
//  OpenGLESShader.cpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "OpenGLESShader.hpp"

#include <stdio.h>
#include <memory>
#include <exception>
#include <vector>

namespace Renderer
{
    OpenGLESShader * OpenGLESShader::Compile(std::string & vertex_shader_source,
                                             std::string & geometry_shader_source,
                                             std::string & fragment_shader_source)
	{
        return this->Compile(vertex_shader_source, fragment_shader_source);
    }
    
    OpenGLESShader * OpenGLESShader::Compile(std::string & vertex_shader_source,
                                             std::string & fragment_shader_source)
	{
        std::vector<std::string> sources = {
                                            vertex_shader_source,
                                            fragment_shader_source
                                           };
        
        GLenum types[2] = {
                           GL_VERTEX_SHADER,
                           GL_FRAGMENT_SHADER
                          };
        
        GLuint shaders[2];
        
		_program = glCreateProgram();
        
        // run through the shader sources
        for(int i = 0; i < 2; i++)
        {
            // create and compile shaders
            shaders[i] = glCreateShader(types[i]);
            const char * c_source = sources[i].c_str();
            glShaderSource(shaders[i], 1, &c_source, nullptr);
            glCompileShader(shaders[i]);
            
            // check compilation results
            GLint compiled;
            glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &compiled);
            if(!compiled)
            {
                GLsizei log_length;
                glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &log_length);
                
                GLchar * shader_log = new GLchar[log_length + 1];
                std::unique_ptr<GLchar> shader_log_unique(shader_log);
                
                glGetShaderInfoLog(shaders[i], log_length, &log_length, shader_log);
                
                printf("%s\n", shader_log);
                
                throw std::exception();
            }
            
            glAttachShader(_program, shaders[i]);
        }
        
        // get explicit locations for attributes
        glBindAttribLocation(_program, 0, "position");
        glBindAttribLocation(_program, 1, "normal");
        glBindAttribLocation(_program, 2, "color");
        
        glLinkProgram(_program);
        
        GLint linked;
        glGetProgramiv(_program, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            GLsizei log_length;
            glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &log_length);
            
            GLchar * shader_log = new GLchar[log_length + 1];
            std::unique_ptr<GLchar> shader_log_unique(shader_log);
            
            glGetShaderInfoLog(_program, log_length, &log_length, shader_log);
            
            printf("%s\n", shader_log);
            
            for(int i = 0; i < 3; i++)
            {
                if(shaders[i] != -1)
                {
                    glDeleteShader(shaders[i]);
                }
            }
            
            throw std::exception();
        }
        
        GLenum error;
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            fprintf(stderr, "%d\n", error);
        }
        
        return this;
    }
    
    void OpenGLESShader::Use()
    {
		glUseProgram(_program);
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

#endif