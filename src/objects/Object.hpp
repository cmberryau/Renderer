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
			explicit Object(std::string & name);
            explicit Object(std::string & name, Transform & transform);
			~Object(){};
			
			bool HasMesh();

			void Update();
			void Draw(const Scene & scene);

			void Add(std::unique_ptr<ObjectAddable> & addable);
			void AddMesh(std::shared_ptr<Mesh> & mesh);
			void AddMeshRenderer(std::unique_ptr<MeshRenderer> & mesh_renderer);

            Transform & LocalTransform();

		private:
            Transform _transform;
			std::string _name;

			std::vector<std::unique_ptr<ObjectAddable>> _children;
			std::vector<std::unique_ptr<ObjectAddable>>::iterator _children_it;
        
			std::shared_ptr<Mesh> _mesh;
			std::unique_ptr<MeshRenderer> _mesh_renderer;
    };
}

#endif // _object_h