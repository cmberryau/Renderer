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
	template <typename T>
	class ObjectType;
    
	template <typename T>
	class MeshRendererType
	{
		public:
			// caches the mesh and prepares it for drawing
            virtual void Store(MeshType<T> * mesh) = 0;

			// draws the mesh
			virtual void Draw(ObjectType<T> * parent_object) = 0;
        
			virtual ~MeshRendererType<T>(){};

		protected:
			MeshRendererType<T>() : _rendering_context(nullptr),
                                    _mesh(nullptr)
			{

			}
        
			MeshType<T> * _mesh;
            RenderingContext * _rendering_context;
	};

	typedef MeshRendererType<float> MeshRenderer;
	typedef MeshRendererType<double> MeshRendererd;
}

#endif // #ifndef _mesh_renderer_h