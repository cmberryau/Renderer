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

#include <vector>

namespace Renderer
{
    class Object
    {
        public:
			~Object();
			Object();

<<<<<<< HEAD
			Transform * LocalTransform();
			void Add(IObjectAddable * object);
			void AddMeshRenderer(MeshRenderer * mesh_renderer);
			void Update();        
			void Draw();
=======
            void Add(IObjectAddableType<T> * object)
            {
                if(object == nullptr)
                    return;
                
                _addables.push_back(object);
                object->Added(this);
            }

			void AddMeshRenderer(MeshRendererType<T> * mesh_renderer)
			{
				if (mesh_renderer == nullptr)
					return;

				_mesh_renderer = mesh_renderer;
			}

            void Update()
            {
                for(int i = 0; i < _addables.size(); i++)
                {
                    if(_addables[i] == nullptr)
                    {
                        return;
                    }
                    
                    _addables[i]->Update(this);
                }
            }
        
			void Draw()
			{
                if(_mesh_renderer != nullptr)
                {
                    _mesh_renderer->Draw(this);
                }
			}
        
            ObjectType<T>() : _mesh_renderer(nullptr)
			{

			}

			~ObjectType<T>()
			{            
                for(int i = 0; i < _addables.size(); i++)
                {
                    delete _addables[i];
                }
			}
>>>>>>> FETCH_HEAD

		protected:
            // required types
            Transform _transform;
        
            // concrete types
			MeshRenderer * _mesh_renderer;
        
            // generically addable types
            std::vector<IObjectAddable *> _addables;        
    };
}

#endif // _object_h