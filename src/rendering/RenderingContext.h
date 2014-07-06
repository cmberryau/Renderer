//
//  RenderingContext.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _renderingcontext_h
#define _renderingcontext_h

#ifdef _WIN32
#include <windows.h>
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "windowing/Window.h"

namespace Renderer
{
	class RenderingContext
	{
		public:
			static RenderingContext * Create(Window * window);

			RenderingContext();
			~RenderingContext();

		protected:
			Window * _window;
			SDL_GLContext _sdl_gl_context;
	};
}

#endif // #ifndef _renderingcontext_h