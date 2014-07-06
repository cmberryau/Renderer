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
	class MeshRenderer
	{
		public:
			~MeshRenderer();

		protected:
			MeshRenderer();
	};
}

#endif // #ifndef _mesh_renderer_h