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
			explicit Object();

			Transform * LocalTransform();
			void Add(IObjectAddable * object);
			void AddMeshRenderer(MeshRenderer * mesh_renderer);
			void Update();        
			void Draw();

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