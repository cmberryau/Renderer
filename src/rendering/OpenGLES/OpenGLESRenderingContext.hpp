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

#ifdef EMSCRIPTEN
#include <SDL/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengles2.h>
#endif

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <exception>

namespace Renderer
{
    template <typename T>
	class OpenGLESRenderingContextType : public RenderingContextType<T>
	{
		public:

            void BeginScene()
            {

            }
        
            void EndScene()
            {

            }

            MeshRendererType<T> * MeshRenderer()
            {
                return new OpenGLESMeshRendererType<T>(this);
            }
        
            class Shader * Shader()
            {
                return new OpenGLESShader();
            }

			OpenGLESRenderingContextType<T>(class Window * window)
			{

			}

			~OpenGLESRenderingContextType<T>()
            {
                
            }
        
		protected:        
   			SDL_GLContext _sdl_gl_context;
	};
    
    typedef OpenGLESRenderingContextType<float> OpenGLESRenderingContext;
    typedef OpenGLESRenderingContextType<double> OpenGLESRenderingContextd;
    
}

#endif // _opengles_renderingcontext_h

#endif // EMSCRIPTEN