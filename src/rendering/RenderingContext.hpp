//
//  RenderingContext.hpp
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

#include "windowing/Window.hpp"
#include "Shader.hpp"

namespace Renderer
{
    template <typename T>
    class MeshRendererType;
    
    template <typename T>
	class RenderingContextType
	{
		public:
            virtual void BeginScene() = 0;
            virtual void EndScene() = 0;
        
            virtual MeshRendererType<T> * MeshRenderer() = 0;
            virtual Shader * Shader() = 0;
        
            Window * Window()
            {
                return _window;
            }
        
			virtual ~RenderingContextType<T>(){}

		protected:
			RenderingContextType<T>(){}
        
			class Window * _window;
	};
    
    typedef RenderingContextType<float> RenderingContext;
    typedef RenderingContextType<double> RenderingContextd;
}

#endif // _renderingcontext_h