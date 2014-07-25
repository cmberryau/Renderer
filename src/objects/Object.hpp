//
//  Object.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _object_h
#define _object_h

#include "math/Transform.hpp"
#include "geometry/Mesh.hpp"
#include "rendering/MeshRenderer.hpp"

namespace Renderer
{
	template <typename T>
    class ObjectType
    {
        public:
			TransformType<T> * LocalTransform()
			{
				return &_transform;
			}

			void AddMesh(MeshType<T> * mesh)
			{
				if (mesh == nullptr)
					return;

				_mesh = mesh;
			}

			void AddMeshRenderer(MeshRendererType<T> * mesh_renderer)
			{
				if (mesh_renderer == nullptr)
					return;

				_mesh_renderer = mesh_renderer;
				_mesh_renderer->Store(_mesh);
			}

			void Draw()
			{
				_mesh_renderer->Draw(this);
			}
        
			ObjectType<T>() : _mesh(nullptr),
					          _mesh_renderer(nullptr)
			{

			}

			~ObjectType<T>()
			{
				delete _mesh;
				delete _mesh_renderer;
			}

		protected:
            TransformType<T> _transform;
			MeshType<T> * _mesh;
			MeshRendererType<T> * _mesh_renderer;
    };

	typedef ObjectType<float> Object;
	typedef ObjectType<double> Objectd;
}

#endif // #ifndef _object_h