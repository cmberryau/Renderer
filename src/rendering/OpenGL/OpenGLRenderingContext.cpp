//
//  OpenGLRenderingContext.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLRenderingContext.hpp"

namespace Renderer
{
	//const int OpenGLRenderingContext::kNumSupportedOpenGLVersions = 9;
	const int OpenGLRenderingContext::kSupportedOpenGLVersions[9][2] = { { 4, 4 }, { 4, 3 }, { 4, 2 },
	{ 4, 1 }, { 4, 0 }, { 3, 3 },
	{ 3, 2 }, { 3, 1 }, { 3, 0 } };

	OpenGLRenderingContext::OpenGLRenderingContext(class Window * window,
		int major_version,
		int minor_version)
	{
		if (window == nullptr)
		{
			throw std::exception();
		}

		// ensure that the requested OpenGL version is supported
		int requested_major_version = major_version;
		int requested_minor_version = minor_version;

		int i = 0;
		for (i = 0; i<kNumSupportedOpenGLVersions; i++)
		{
			if (kSupportedOpenGLVersions[i][0] == requested_major_version &&
				kSupportedOpenGLVersions[i][1] == requested_minor_version)
			{
				break;
			}
		}

		// if it's not, just go from the top
		if (i == kNumSupportedOpenGLVersions)
		{
			requested_major_version = kSupportedOpenGLVersions[0][0];
			requested_minor_version = kSupportedOpenGLVersions[0][1];
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // required for osx
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, requested_major_version);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, requested_minor_version);

		_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);

		// run through the other supported versions if requested/top version fails
		i = 0;
		while (_sdl_gl_context == nullptr && i < kNumSupportedOpenGLVersions)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // required for osx
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, kSupportedOpenGLVersions[i][0]);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, kSupportedOpenGLVersions[i][1]);

			_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);

			i++;
		}

		if (_sdl_gl_context == nullptr)
		{
			throw std::exception();
		}

		CheckForGLError();

#ifdef _WIN32
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			throw std::exception("glewInit failed!\n");
		}
#endif

		GLint actual_major_version = -1;
		GLint actual_minor_version = -1;

		glGetIntegerv(GL_MAJOR_VERSION, &actual_major_version);
		CheckForGLError();
		glGetIntegerv(GL_MINOR_VERSION, &actual_minor_version);
		CheckForGLError();

		fprintf(stdout, "OpenGL version: %d.%d\n", actual_major_version, actual_minor_version);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		CheckForGLError();
	}

	OpenGLRenderingContext::~OpenGLRenderingContext()
	{

	}

	bool OpenGLRenderingContext::CheckForGLError()
	{
		GLenum error;
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			fprintf(stderr, "OpenGL error: %d\n", error);
			return true;
		}

		return false;
	}

	void OpenGLRenderingContext::BeginScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderingContext::EndScene()
	{

	}

	class MeshRenderer * OpenGLRenderingContext::MeshRenderer()
	{
		return new OpenGLMeshRenderer(this);
	}

	class Shader * OpenGLRenderingContext::Shader()
	{
		return new OpenGLShader();
	}
}