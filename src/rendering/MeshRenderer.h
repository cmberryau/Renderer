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

	typedef ObjectType<float> Object;
	typedef ObjectType<double> Objectd;

	template <typename T>
	class MeshRendererType
	{
		public:
			static MeshRendererType<T> * Create(RenderingContext * rendering_context)
			{
				MeshRenderer * mesh_renderer = nullptr;

				if (rendering_context->Type() == OpenGLContextType)
				{
					mesh_renderer = OpenGLMeshRenderer::Create(rendering_context);
				}

				return mesh_renderer;
			}

			// caches the mesh and prepares it for drawing
            virtual void Store(Mesh * mesh) = 0;

			// draws the mesh
			virtual void Draw(Object * parent_object) = 0;
        
			virtual ~MeshRendererType(){};

		protected:
			MeshRendererType() : _rendering_context(nullptr),
							     _mesh(nullptr)
			{

			}
        
			Mesh * _mesh;
            RenderingContext * _rendering_context;
	};

	typedef MeshRendererType<float> MeshRenderer;
	typedef MeshRendererType<double> MeshRendererd;
}

#endif // #ifndef _mesh_renderer_h