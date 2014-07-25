//
//  MeshRendererFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 24/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_renderer_factory_h
#define _mesh_renderer_factory_h

#include "MeshRenderer.hpp"

namespace Renderer
{
	template <typename T>
	class MeshRendererFactory
	{
		MeshRendererType<T> * Create(RenderingContext * rendering_context)
		{
			if (rendering_context->Type() == OpenGLContextType)
			{

			}

			return nullptr;
		}
	};	
}

#endif // _mesh_renderer_factory_h