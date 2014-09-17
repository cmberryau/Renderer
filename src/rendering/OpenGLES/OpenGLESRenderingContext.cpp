//
//  OpenGLESRenderingContext.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "OpenGLESRenderingContext.hpp"

namespace Renderer
{
	OpenGLESRenderingContext::OpenGLESRenderingContext(class Window * window)
	{
		if (window == nullptr)
		{
			throw std::exception();
		}

		_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);

#ifdef _WIN32
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			throw std::exception("glewInit failed!\n");
		}
#endif

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
			}

	OpenGLESRenderingContext::~OpenGLESRenderingContext()
	{

	}

	void OpenGLESRenderingContext::BeginScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLESRenderingContext::EndScene()
	{

	}

	MeshRenderer * OpenGLESRenderingContext::MeshRenderer()
	{
		return new OpenGLESMeshRenderer(this);
	}

	class Shader * OpenGLESRenderingContext::Shader()
	{
		return new OpenGLESShader();
	}
}

#endif // EMSCRIPTEN