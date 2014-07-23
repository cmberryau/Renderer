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
	template <typename T>
    class MeshType
    {
        public:
			// factory constructor
			static MeshType<T> * Create(Vector3<T> * vertices, unsigned int size)
			{
				// confirm the passed data
				if (vertices == nullptr)
					return nullptr;

				Mesh * mesh = new Mesh();

				mesh->_vertices = new Vector3<T>[size];

				if (mesh->_vertices == nullptr)
					return nullptr;

				for (unsigned int i = 0; i < size; i++)
				{
					if (vertices[i] == nullptr)
						return nullptr;

					mesh->_vertices[i] = vertices[i];
				}

				mesh->_vertices_count = size;

				return mesh;
			}

			~MeshType<T>()
			{
				delete _vertices;
				delete _vertex_colors;
				delete _triangles;
			}
        
			// vertex related
			void SetVertices(Vector3<T> vertices, unsigned int size)
			{
				this->_vertices = new Vector3<T>[size];

				if (this->_vertices == nullptr)
					return;

				for (unsigned int i = 0; i < size; i++)
				{
					if (vertices[i] == nullptr)
						return;

					this->_vertices[i] = vertices[i];
				}

				this->_vertices_count = size;
			}

			const Vector3<T> * Vertices()
			{
				return (const Vector3<T> *)_vertices;
			}

			unsigned int VerticesSize()
			{
				return _vertices_count * Vector3<T>::Size();
			}

			unsigned int VerticesCount()
			{
				return _vertices_count;
			}

			// vertex color related
			void SetColors(Vector4f * vertex_colors, unsigned int size)
			{
				this->_vertex_colors = new Vector4f[size];

				if (this->_vertex_colors == nullptr)
					return;

				for (unsigned int i = 0; i < size; i++)
				{
					if (vertex_colors[i] == nullptr)
						return;

					this->_vertex_colors[i] = vertex_colors[i];
				}

				this->_vertex_colors_count = size;
			}

			const Vector4f * Colors()
			{
				return (const Vector4f *)_vertex_colors;
			}

			unsigned int ColorsSize()
			{
				return _vertex_colors_count * Vector4f::Size();
			}

			unsigned int ColorsCount()
			{
				return _vertex_colors_count;
			}

			// triangle related
			void SetTriangles(Vector3ui * triangles, unsigned int size)
			{
				this->_triangles = new Vector3ui[size];

				if (this->_triangles == nullptr)
					return;

				for (unsigned int i = 0; i < size; i++)
				{
					if (triangles[i] == nullptr)
						return;

					this->_triangles[i] = triangles[i];
				}

				this->_triangles_count = size;
			}

			const Vector3ui * Triangles()
			{
				return (const Vector3ui *)_triangles;
			}

			unsigned int TrianglesSize()
			{
				return _triangles_count * Vector3ui::Size();
			}

			unsigned int TrianglesCount()
			{
				return _triangles_count;
			}
        
			// debug output
			void Print()
			{
				for (unsigned int i = 0; i < _vertices_count; i++)
				{
					if (_vertices[i] == nullptr)
					{
						fprintf(stderr, "Error: Found a mesh with a null vertex reference\n");
						return;
					}

					_vertices[i].Print();
				}
			}

		protected:
			// can only create from the above factory method
			MeshType<T>() : _vertices(nullptr), _vertices_count(0),
							_vertex_colors(nullptr), _vertex_colors_count(0),
							_triangles(nullptr), _triangles_count(0)
			{

			}
        
			// vertex related
            Vector3<T> * _vertices;
            unsigned int _vertices_count;

			// vertex color related
			Vector4f * _vertex_colors;
			unsigned int _vertex_colors_count;

			// triangle related
			Vector3ui * _triangles;
			unsigned int _triangles_count;
    };

	typedef MeshType<float> Mesh;
	typedef MeshType<double> Meshd;
}

#endif // #ifndef _object_h