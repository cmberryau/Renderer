//
//  OpenGLMeshRenderer.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_mesh_renderer_h
#define _opengl_mesh_renderer_h

#include "rendering/MeshRenderer.h"

namespace Renderer
{
	class OpenGLMeshRenderer : public MeshRenderer
	{
		public:
            void Store(Mesh * mesh);
            void Draw();
        
			~OpenGLMeshRenderer();
			OpenGLMeshRenderer();

		protected:			
            RenderingContext * _rendering_context;
            
	};
}

#endif // #ifndef _opengl_mesh_renderer_h