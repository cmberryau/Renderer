//
//  Object.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _object_h
#define _object_h

#include "math/Transform.h"
#include "geometry/Mesh.h"
#include "rendering/MeshRenderer.h"

namespace Renderer
{
    class Object
    {
        public:
			Transform * Transform();
			void AddMesh(Mesh * mesh);
			void AddMeshRenderer(MeshRenderer * mesh_renderer);
            void Draw();
        
            Object();
            ~Object();

		protected:
			class Transform _transform;
			Mesh * _mesh;
			MeshRenderer * _mesh_renderer;
    };
}

#endif // #ifndef _object_h