//
//  Mesh.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_h
#define _mesh_h

#include "math/Vector.hpp"

namespace Renderer
{
	template <typename T>
    class MeshType
    {
        public:
			MeshType<T>() : _vertices(nullptr), _vertices_count(0),
							_vertex_colors(nullptr), _vertex_colors_count(0),
							_triangles(nullptr), _triangles_count(0)
			{

			}

			~MeshType<T>()
			{
				delete _vertices;
				delete _vertex_colors;
				delete _triangles;
			}
        
			void Validate()
			{
				if (this->Vertices() == nullptr ||
					this->Colors() == nullptr ||
					this->Triangles() == nullptr)
				{
					// todo : throw error
					return;
				}

				if (this->VerticesCount() != this->ColorsCount())
				{
					// todo : throw error
					return;
				}

				for (unsigned int i = 0; i < this->TrianglesCount(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (this->Triangles()[i][j] > this->VerticesCount() - 1)
						{
							// todo : throw error
							return;
						}
					}
				}
			}

			// vertex related
			void SetVertices(Vector4<T> * vertices, unsigned int size)
			{
				this->_vertices = new Vector4<T>[size];

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

			const Vector4<T> * Vertices()
			{
				return (const Vector4<T> *)_vertices;
			}

			unsigned int VerticesSize()
			{
				return _vertices_count * Vector4<T>::Size();
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
			// vertex related
            Vector4<T> * _vertices;
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