//
//  OpenGLRenderingContext.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_renderingcontext_h
#define _opengl_renderingcontext_h

#include "rendering/RenderingContext.h"

namespace Renderer
{
	class OpenGLRenderingContext : public RenderingContext
	{
		public:
            static OpenGLRenderingContext * Create(Window * window);
			~OpenGLRenderingContext();
        
            RenderingContextType Type();
            void BeginScene();
            void EndScene();
        
		protected:
            OpenGLRenderingContext();
        
   			SDL_GLContext _sdl_gl_context;
	};
}

#endif // #ifndef _opengl_renderingcontext_h