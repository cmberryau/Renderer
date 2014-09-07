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
		if (vertex_shader_source == nullptr || fragment_shader_source == nullptr)
		{
			throw std::exception();
		}

		std::unique_ptr<char> vertex_shader_source_unique(vertex_shader_source);
		std::unique_ptr<char> fragment_shader_source_unique(fragment_shader_source);

		const char * sources[2] = { vertex_shader_source,
									fragment_shader_source };

		GLenum types[2] = { GL_VERTEX_SHADER,
							GL_FRAGMENT_SHADER };

		GLuint shaders[3];

		_program = glCreateProgram();

		// run through the shader sources
		for (int i = 0; i < 2; i++)
		{
			if (sources[i] == nullptr)
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
			if (!compiled)
			{
				GLsizei log_length;
				glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &log_length);

				GLchar * shader_log = new GLchar[log_length + 1];
				glGetShaderInfoLog(shaders[i], log_length, &log_length, shader_log);

				printf("%s\n", shader_log);

				delete[] shader_log;

				return nullptr;
			}

			glAttachShader(_program, shaders[i]);
		}

		glLinkProgram(_program);

		GLint linked;
		glGetProgramiv(_program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei log_length;
			glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &log_length);

			GLchar * shader_log = new GLchar[log_length + 1];
			glGetShaderInfoLog(_program, log_length, &log_length, shader_log);

			printf("%s\n", shader_log);

			delete[] shader_log;

			for (int i = 0; i < 3; i++)
			{
				if (shaders[i] != -1)
				{
					glDeleteShader(shaders[i]);
				}
			}

			return nullptr;
		}

		GLenum error;
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			fprintf(stderr, "%d\n", error);
		}

        return this;
    }
    
    OpenGLESShader * OpenGLESShader::Compile(char * vertex_shader_source,
                                             char * geometry_shader_source,
                                             char * fragment_shader_source)
	{
		// there should not be any geometry shader source for opengles
		if (geometry_shader_source != nullptr)
		{
			throw std::exception();
		}

        return this->Compile(vertex_shader_source, fragment_shader_source);
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
