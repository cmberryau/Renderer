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
#include <memory>

namespace Renderer
{
	template <typename T>
    class MeshType
    {
        public:
			MeshType<T>() : _vertices(nullptr), _vertices_count(0),
							_vertex_normals(nullptr), _vertex_normals_count(0),
							_vertex_colors(nullptr), _vertex_colors_count(0),
							_triangles(nullptr), _triangles_count(0)
			{

			}

			~MeshType<T>()
			{
				delete _vertices;
				delete _vertex_normals;
				delete _vertex_colors;
				delete _triangles;
			}
        
			void Validate()
			{
				// as a baseline, meshes must contain vertices and triangles
				if (this->Vertices() == nullptr ||
					this->Triangles() == nullptr)
				{
					// todo : throw error
					return;
				}

				// if the mesh does not contain vertex colors, we assign default ones
				if (this->Colors() == nullptr)
				{
					Vector4f * default_colors = new Vector4f[this->VerticesCount()];
					std::unique_ptr<Vector4f> default_colors_unique(default_colors);

					for (unsigned int i = 0; i < this->VerticesCount(); i++)
					{
						default_colors[i] = MeshType<T>::kDefaultVertexColor;
					}

					this->SetColors(default_colors, this->VerticesCount());
				}

				// there must be a color for each vertex
				if (this->VerticesCount() != this->ColorsCount())
				{
					// todo : throw error
					return;
				}

				// the triangle references must not be outside the vertex buffer
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

			// vertex normal related
			void SetVertexNormals(Vector3<T> * vertex_normals, unsigned int size)
			{
				this->_vertex_normals = new Vector3<T>[size];

				if (this->_vertex_normals == nullptr)
					return;

				for (unsigned int i = 0; i < size; i++)
				{
					if (vertex_normals[i] == nullptr)
						return;

					this->_vertex_normals = vertex_normals[i];
				}

				this->_vertex_normals_count = size;
			}
			
			const Vector3<T> * VertexNormals()
			{
				return (const Vector3<T> *)_vertex_normals;
			}

			unsigned int VertexNormalsSize()
			{
				return _vertex_normals_count * Vector3<T>::Size();
			}

			unsigned int VertexNormalsCount()
			{
				return _vertex_normals_count;
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
			// vertices
            Vector4<T> * _vertices;
            unsigned int _vertices_count;

			// vertex normals
			Vector3<T> * _vertex_normals;
			unsigned int _vertex_normals_count;

			// vertex colors
			Vector4f * _vertex_colors;
			unsigned int _vertex_colors_count;

			// triangles
			Vector3ui * _triangles;
			unsigned int _triangles_count;

			// default vertex color
			static const Vector4f kDefaultVertexColor;
    };

	template <typename T>
	const Vector4f MeshType<T>::kDefaultVertexColor = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);

	typedef MeshType<float> Mesh;
	typedef MeshType<double> Meshd;
}

#endif // _mesh_h