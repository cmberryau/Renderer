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
#include "objects/ObjectAddable.hpp"
#include "rendering/MeshRenderer.hpp"

#include <vector>

namespace Renderer
{
    class Scene;
    
    class Object
    {
        public:
			explicit Object();
			~Object(){};
			
			void Update();
			void Draw(const Scene & scene);

			void Add(std::shared_ptr<ObjectAddable> & addable);
			void AddMeshRenderer(std::shared_ptr<MeshRenderer> & mesh_renderer);

			const Transform & LocalTransform() const;

		private:
            Transform _transform;

			std::vector<std::shared_ptr<ObjectAddable>> _children;
			std::vector<std::shared_ptr<ObjectAddable>>::iterator _children_it;
			std::shared_ptr<MeshRenderer> _mesh_renderer;
    };
}

#endif // _object_h