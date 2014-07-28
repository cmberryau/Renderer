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
#include "rendering/Camera.hpp"
#include "objects/IObjectAddable.hpp"

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

            void AddComponent(IObjectAddableType<T> * object)
            {
                if(object == nullptr)
                    return;
                
                _added_object = object;
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

            void Update()
            {
                if(_added_object == nullptr)
                    return;
                
                _added_object->Update(this);
            }
        
			void Draw()
			{
                if(_mesh_renderer != nullptr)
                {
                    _mesh_renderer->Draw(this);
                }
			}
        
			ObjectType<T>() : _mesh(nullptr),
					          _mesh_renderer(nullptr),
                              _added_object(nullptr)
			{

			}

			~ObjectType<T>()
			{
				delete _mesh;
				delete _mesh_renderer;
                delete _added_object;
			}

		protected:
            // required types
            TransformType<T> _transform;
        
            // concrete types
			MeshType<T> * _mesh;
			MeshRendererType<T> * _mesh_renderer;
            CameraType<T> * _camera;
        
            // generically addable types
            IObjectAddableType<T> * _added_object;
        
    };

	typedef ObjectType<float> Object;
	typedef ObjectType<double> Objectd;
}

#endif // #ifndef _object_h