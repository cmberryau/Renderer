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
	enum RenderingContextType {
		OpenGLContextType,
		DirectX11ContextType
	};

	class RenderingContext
	{
		public:
			static RenderingContext * Create(Window * window,
											 RenderingContextType context_type);
			virtual RenderingContextType Type() = 0;
            virtual void BeginScene() = 0;
            virtual void EndScene() = 0;
        
			virtual ~RenderingContext();

		protected:
            RenderingContext();
        
			Window * _window;
			RenderingContextType _context_type;
	};
}

#endif // #ifndef _renderingcontext_h