//
//  Mesh.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_h
#define _mesh_h

#include "math\Vector.h"

namespace Renderer
{
    class Mesh
    {
        public:
			// factory constructor
			static Mesh * Create(Vector3f * verticies, unsigned int size);
            ~Mesh();

			// debug output
			void Print();

		protected:
			// can only create from the above factory method
			Mesh();
			Vector3f * _vertices;
			unsigned int _vertices_count;
    };
}

#endif // #ifndef _object_h