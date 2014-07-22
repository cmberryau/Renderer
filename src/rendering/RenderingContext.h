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
	enum RenderingContextType 
	{
		UnknownContextType,
		OpenGLContextType,
		DirectX11ContextType
	};

	enum RenderingContextPrecision
	{
		FloatPrecision,
		DoublePrecision
	};

	class RenderingContext
	{
		public:
			RenderingContextType Type();
			virtual RenderingContextPrecision Precision() = 0;

            virtual void BeginScene() = 0;
            virtual void EndScene() = 0;
        
			virtual ~RenderingContext();

		protected:
			RenderingContext(RenderingContextType context_type,
							 RenderingContextPrecision context_precision);
        
			Window * _window;
			RenderingContextType _context_type;
			RenderingContextPrecision _precision;
	};
}

#endif // #ifndef _renderingcontext_h