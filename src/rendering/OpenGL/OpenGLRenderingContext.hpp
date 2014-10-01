//
//  OpenGLRenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#ifndef _opengl_renderingcontext_h
#define _opengl_renderingcontext_h

#include "rendering/RenderingContext.hpp"
#include "rendering/OpenGL/OpenGLMeshRenderer.hpp"

// OpenGL includes
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#ifdef EMSCRIPTEN
#include <SDL/SDL_opengl.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <exception>

namespace Renderer
{
	class OpenGLRenderingContext : public RenderingContext
	{
		public:
			static const int kNumSupportedOpenGLVersions = 9;
            static const int kSupportedOpenGLVersions[9][2];

			explicit OpenGLRenderingContext(class Window * window,
            int major_version = kSupportedOpenGLVersions[0][0],
			int minor_version = kSupportedOpenGLVersions[0][1]);

			~OpenGLRenderingContext();

			static bool CheckForGLError();
			
			void BeginScene();        
			void EndScene();

			class MeshRenderer * MeshRenderer();        
			class Shader * Shader();
        
		protected:        
   			SDL_GLContext _sdl_gl_context;
	};
}

#endif // _opengl_renderingcontext_h

#endif // !EMSCRIPTEN