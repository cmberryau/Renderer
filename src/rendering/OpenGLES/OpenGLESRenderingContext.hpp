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

#include "windowing/Window.hpp"
#include "rendering/RenderingContext.hpp"
#include "rendering/OpenGLES/OpenGLESMeshRenderer.hpp"
#include "rendering/OpenGLES/OpenGLESCommon.hpp"

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <exception>

namespace Renderer
{
	class OpenGLESRenderingContext : public RenderingContext
	{
		public:
			explicit OpenGLESRenderingContext(const Window & window);
			~OpenGLESRenderingContext();

            virtual void BeginScene() const override;
            virtual void EndScene() const override;
	};
}

#endif // _opengles_renderingcontext_h

#endif // EMSCRIPTEN