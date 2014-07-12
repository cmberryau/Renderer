//
//  Mesh.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_h
#define _mesh_h

#include "math/Vector.h"

namespace Renderer
{
    class Mesh
    {
        public:
			// factory constructor
			static Mesh * Create(Vector3f * verticies, unsigned int size);
            ~Mesh();
        
			// vertex related
            void SetVertices(Vector3f * vertices, unsigned int size);        
            const Vector3f * Vertices();
            unsigned int VerticesSize();
            unsigned int VerticesCount();

			// vertex color related
			void SetColors(Vector4f * colors, unsigned int size);
			const Vector4f * Colors();
			unsigned int ColorsSize();
			unsigned int ColorsCount();

			// triangle related
			void SetTriangles(Vector3ui * triangles, unsigned int size);
			const Vector3ui * Triangles();
			unsigned int TrianglesSize();
			unsigned int TrianglesCount();
        
			// debug output
			void Print();

		protected:
			// can only create from the above factory method
			Mesh();
        
			// vertex related
            Vector3f * _vertices;
            unsigned int _vertices_count;

			// vertex color related
			Vector4f * _vertex_colors;
			unsigned int _vertex_colors_count;

			// triangle related
			Vector3ui * _triangles;
			unsigned int _triangles_count;
    };
}

#endif // #ifndef _object_h