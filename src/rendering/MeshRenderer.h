//
//  MeshRenderer.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_renderer_h
#define _mesh_renderer_h

#include "RenderingContext.h"
#include "geometry/Mesh.h"

namespace Renderer
{
	class Object;

	class MeshRenderer
	{
		public:
            static MeshRenderer * Create(RenderingContext * rendering_context);

			// caches the mesh and prepares it for drawing
            virtual void Store(Mesh * mesh) = 0;
			// draws the mesh
			virtual void Draw(Object * parent_object) = 0;
        
			virtual ~MeshRenderer();

		protected:
			MeshRenderer();
        
			Mesh * _mesh;
			Object * _parent_object;
            RenderingContext * _rendering_context;
	};
}

#endif // #ifndef _mesh_renderer_h