//
//  OpenGLESRenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 04/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#ifndef _opengles_renderingcontext_h
#define _opengles_renderingcontext_h

#include "rendering/RenderingContext.hpp"
#include "rendering/OpenGLES/OpenGLESMeshRenderer.hpp"

#include <SDL2/SDL_opengles2.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <exception>

namespace Renderer
{
	class OpenGLESRenderingContext : public RenderingContext
	{
		public:
			OpenGLESRenderingContext(class Window * window);
			~OpenGLESRenderingContext();

			void BeginScene();        
			void EndScene();

			class MeshRenderer * MeshRenderer();        
			class Shader * Shader();

		protected:
			SDL_GLContext _sdl_gl_context;
	}; 
}

#endif // _opengles_renderingcontext_h

#endif // EMSCRIPTEN