//
//  OpenGLRenderingContext.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#include "OpenGLRenderingContext.hpp"
#include "utility/IO.hpp"

#include <algorithm>

namespace Renderer
{
	void OpenGLRenderingContext::Init(const Window & window,
									  int desired_major_version,
									  int desired_minor_version)
	{
		if (!!_sdl_gl_context)
		{
			throw std::runtime_error("Tried to Init a OpenGLRenderingContext twice");
		}

		_supported_opengl_versions.push_back(OpenGLVersion(4, 4));
		_supported_opengl_versions.push_back(OpenGLVersion(4, 1));		

		// first attempt to match the passed values, if any
		std::vector<OpenGLVersion>::iterator it;
		if (desired_major_version != 0 && desired_minor_version != 0)
		{
			OpenGLVersion desired_version(desired_major_version, desired_minor_version);
			it = std::find(_supported_opengl_versions.begin(),
						   _supported_opengl_versions.end(), desired_version);

			if (it != _supported_opengl_versions.end())
			{
				_sdl_gl_context = CreateSDLContext(window, desired_version);

				if (!!_sdl_gl_context)
				{
					if (CurrentOpenGLVersion() == desired_version)
					{
						SetupDefaultGLAttributes();
						return;
					}
					else
					{
						throw std::runtime_error("SDL returned incorrect OpenGL version");
					}
				}
			}
		}

		// run through the supported versions if that does not work out
		for (it = _supported_opengl_versions.begin();
			 it != _supported_opengl_versions.end();
			 ++it)
		{
			_sdl_gl_context = CreateSDLContext(window, *it);

			if (!!_sdl_gl_context)
			{
				if (CurrentOpenGLVersion() == *it)
				{
					SetupDefaultGLAttributes();
					return;
				}
				else
				{
					throw std::runtime_error("SDL returned incorrect OpenGL version");
				}
			}
		}

		throw std::runtime_error("Unable to find supported OpenGL context");
	}

	std::unique_ptr<SDL_GLContext, OpenGLRenderingContext::SDL_GLContextDeleter> 
	OpenGLRenderingContext::CreateSDLContext(const Window & window, const OpenGLVersion & version_to_create)
	{
		// required for osx
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version_to_create._major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version_to_create._minor);

		SDL_GLContext sdl_context = SDL_GL_CreateContext(window.GetSDLWindow());		

		if (sdl_context == nullptr)
		{
            return nullptr;
		}

		std::unique_ptr<SDL_GLContext, SDL_GLContextDeleter> sdl_context_ptr(&sdl_context);

		CheckForGLError();

#ifdef _WIN32
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			throw std::exception("glewInit failed!\n");
		}

		// glewInit() throws 1280 error always, known bug
		try
		{
			CheckForGLError();
		}
		catch (std::exception e)
		{
			// just swallow the exception
		}
#endif	
		
		return sdl_context_ptr;
	}

	OpenGLRenderingContext::OpenGLVersion OpenGLRenderingContext::CurrentOpenGLVersion() const
	{
		GLint major_version = -1;
		GLint minor_version = -1;

		glGetIntegerv(GL_MAJOR_VERSION, &major_version);
		glGetIntegerv(GL_MINOR_VERSION, &minor_version);
		CheckForGLError();

		return OpenGLVersion(major_version, minor_version);
	}

	void OpenGLRenderingContext::SetupDefaultGLAttributes()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// hacked in default material creation
		std::string vertex_shader_path("src/shaders/GLSL/default.vert");
		std::string fragment_shader_path("src/shaders/GLSL/default.frag");
		std::string vertex_shader_source = IO::ReadFile(vertex_shader_path);
		std::string fragment_shader_source = IO::ReadFile(fragment_shader_path);
		_default_shader = CreateShader(vertex_shader_source, fragment_shader_source);
		_default_material = std::make_shared<Material>(_default_shader);

		CheckForGLError();
	}

	bool OpenGLRenderingContext::IsReady() const
	{
		return !!_sdl_gl_context;
	}

	OpenGLRenderingContext::OpenGLRenderingContext(const Window & window)
	{
		Init(window);
	}

	OpenGLRenderingContext::OpenGLRenderingContext(const Window & window,
												   int desired_major_version,
												   int desired_minor_version)
	{
		Init(window, desired_major_version, desired_minor_version);
	}

	void OpenGLRenderingContext::BeginScene() const
	{
		if (IsReady())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}		
	}

	void OpenGLRenderingContext::EndScene() const
	{

	}

	std::unique_ptr<MeshRenderer> OpenGLRenderingContext::CreateMeshRenderer() const
	{
		return std::unique_ptr<MeshRenderer>(new OpenGLMeshRenderer());
	}

	std::shared_ptr<Material> OpenGLRenderingContext::DefaultMaterial() const
	{
		return _default_material;
	}

	std::shared_ptr<Shader> OpenGLRenderingContext::CreateShader(std::string & vertex_source,
															     std::string & fragment_source) const
	{
		std::shared_ptr<Shader> shader(new OpenGLShader());
		shader->Compile(vertex_source, fragment_source);

		return shader;
	}

	std::shared_ptr<Shader> OpenGLRenderingContext::CreateShader(std::string & vertex_source,
															     std::string & geometry_source,
															     std::string & fragment_source) const
	{
		std::shared_ptr<Shader> shader(new OpenGLShader());
		shader->Compile(vertex_source, geometry_source, fragment_source);

		return shader;
	}
}

#endif // !EMSCRIPTEN