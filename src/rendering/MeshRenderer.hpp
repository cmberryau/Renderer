//
//  MeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_renderer_h
#define _mesh_renderer_h

#include "rendering/RenderingContext.hpp"
#include "geometry/Mesh.hpp"
#include "objects/Object.hpp"
#include "rendering/Material.hpp"

namespace Renderer
{	
	class Object;

	class MeshRenderer
	{
		public:
			// caches the mesh and prepares it for drawing
			virtual void SetMesh(Mesh * mesh) = 0;
		
			// sets the material
			void SetMaterial(Material * material);

			// draws the mesh
			virtual void Draw(Object * parent_object) = 0;
		
			virtual ~MeshRenderer(){};

		protected:
			explicit MeshRenderer(RenderingContext * rendering_context);
		
			Mesh * _mesh;
			Material * _material;
			RenderingContext * _rendering_context;
	};
}

#endif // _mesh_renderer_h