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
	template <typename T>
	class MeshRendererType
	{
		public:
			// caches the mesh and prepares it for drawing
            virtual void SetMesh(MeshType<T> * mesh) = 0;
        
            // sets the material
            void SetMaterial(Material * material)
            {
                _material = material;
            }

			// draws the mesh
			virtual void Draw(ObjectType<T> * parent_object) = 0;
        
			virtual ~MeshRendererType<T>(){};

		protected:
			MeshRendererType<T>() : _rendering_context(nullptr),
                                    _mesh(nullptr)
			{

			}
        
			MeshType<T> * _mesh;
            Material * _material;
            RenderingContext * _rendering_context;
	};

	typedef MeshRendererType<float> MeshRenderer;
	typedef MeshRendererType<double> MeshRendererd;
}

#endif // _mesh_renderer_h