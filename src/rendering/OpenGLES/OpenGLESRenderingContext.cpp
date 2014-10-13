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
	OpenGLESRenderingContext::OpenGLESRenderingContext(const Window & window)
	{
		SDL_GLContext sdl_gl_context = SDL_GL_CreateContext(window.GetSDLWindow());

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

	void OpenGLESRenderingContext::BeginScene() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLESRenderingContext::EndScene() const
	{

	}
}

#endif // EMSCRIPTEN