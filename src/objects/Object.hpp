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

			void Update();
			void Draw(const Scene & scene);
			
			void AddChild(std::unique_ptr<Object> & object);
			std::size_t GetChildCount();
			std::vector<std::unique_ptr<Object>> & GetChildren();

			bool HasMesh();
			void AddMesh(std::shared_ptr<Mesh> & mesh);
			void AddMeshRenderer(std::unique_ptr<MeshRenderer> & mesh_renderer);

            Transform & LocalTransform();

		private:
            Transform _transform;
			std::string _name;
			std::vector<std::unique_ptr<Object>> _children;        
			std::shared_ptr<Mesh> _mesh;
			std::unique_ptr<MeshRenderer> _mesh_renderer;
    };
}

#endif // _object_h