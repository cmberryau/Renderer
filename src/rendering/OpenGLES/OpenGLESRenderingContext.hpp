//
//  OpenGLESRenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 04/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

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
    template <typename T>
	class OpenGLESRenderingContextType : public RenderingContextType<T>
	{
		public:
            void BeginScene()
            {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
				if (window == nullptr)
				{
					throw std::exception();
				}

				_sdl_gl_context = SDL_GL_CreateContext(window->_sdl_window);

				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CW);
				glCullFace(GL_BACK);

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);
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