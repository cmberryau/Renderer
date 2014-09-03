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

#include <exception>
#include <memory>
#include <map>
#include <vector>

namespace Renderer
{
	template <typename T>
    class MeshType
    {
        public:
			MeshType<T>() : _vertices(nullptr), _vertex_count(0),
							_vertex_normals(nullptr), _vertex_normals_count(0),
							_vertex_colors(nullptr), _vertex_colors_count(0),
							_triangles(nullptr), _triangle_count(0)
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
				// if the mesh is missing normals, we will calculate them
				if (_vertices == nullptr || _triangles == nullptr)
				{
					throw std::exception();
				}

				// the triangle references must not be outside the vertex buffer
				for (unsigned int i = 0; i < _triangle_count; ++i)
				{
					for (int j = 0; j < 3; j++)
					{
						if (_triangles[i][j] > _vertex_count - 1)
						{
							throw std::exception();
						}
					}
				}

				// validate normals
				if (!ValidateNormals())
				{
					throw std::exception();
				}

				// validate the vertex colors
				if (!ValidateColors())
				{
					throw std::exception();
				}
			}

			// vertex related
			void SetVertices(Vector4<T> * vertices, unsigned int size)
			{
				this->_vertices = new Vector4<T>[size];

				if (this->_vertices == nullptr)
					return;

				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertices[i] == nullptr)
						return;

					this->_vertices[i] = vertices[i];
				}

				this->_vertex_count = size;
			}

			const Vector4<T> * Vertices()
			{
				return static_cast<const Vector4<T> *>(_vertices);
			}

			unsigned int VerticesSize()
			{
				return _vertex_count * Vector4<T>::Size();
			}

			unsigned int VertexCount()
			{
				return _vertex_count;
			}

			// vertex normal related
			void SetVertexNormals(Vector3<T> * vertex_normals, unsigned int size)
			{
				this->_vertex_normals = new Vector3<T>[size];

				if (this->_vertex_normals == nullptr)
					return;

				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertex_normals[i] == nullptr)
						return;

					this->_vertex_normals[i] = vertex_normals[i];
				}

				this->_vertex_normals_count = size;
			}
			
			const Vector3<T> * VertexNormals()
			{
				return static_cast<const Vector3<T> *>(_vertex_normals);
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

				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertex_colors[i] == nullptr)
						return;

					this->_vertex_colors[i] = vertex_colors[i];
				}

				this->_vertex_colors_count = size;
			}

			const Vector4f * Colors()
			{
				return static_cast<const Vector4f *>(_vertex_colors);
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

				for (unsigned int i = 0; i < size; ++i)
				{
					if (triangles[i] == nullptr)
						return;

					this->_triangles[i] = triangles[i];
				}

				this->_triangle_count = size;
			}

			const Vector3ui * Triangles()
			{
				return static_cast<const Vector3ui *>(_triangles);
			}

			unsigned int TrianglesSize()
			{
				return _triangle_count * Vector3ui::Size();
			}

			unsigned int TrianglesCount()
			{
				return _triangle_count;
			}
        
			// debug output
			void Print()
			{
				for (unsigned int i = 0; i < _vertex_count; ++i)
				{
					if (_vertices[i] == nullptr)
					{
						throw std::exception();
					}

					_vertices[i].Print();
				}
			}

		protected:
			bool ValidateColors()
			{
				// if the mesh does not contain vertex colors, we assign default ones
				if (_vertex_colors == nullptr)
				{
					Vector4f * default_colors = new Vector4f[_vertex_count];
					std::unique_ptr<Vector4f> default_colors_unique(default_colors);

					for (unsigned int i = 0; i < _vertex_count; ++i)
					{
						default_colors[i] = MeshType<T>::kDefaultVertexColor;
					}

					this->SetColors(default_colors, _vertex_count);
				}
				// there must be a color for each vertex
				else if (_vertex_count != _vertex_colors_count)
				{
					return false;
				}

				return true;
			}

			bool ValidateNormals()
			{
				// if the mesh does not contain vertex normals, we must assign some
				if (_vertex_normals == nullptr)
				{
					// because we are not provided with any normals, we do not assume to smooth
					// or guess normals, this could confuse the user and provide unexpected results
					Vector3<T> * default_normals = new Vector3<T>[_triangle_count * 3];
					std::unique_ptr<Vector3<T>> default_normals_unique(default_normals);

					Vector4<T> * default_vertices = new Vector4<T>[_triangle_count * 3];
					std::unique_ptr<Vector4<T>> default_vertices_unique(default_vertices);

					Vector3ui * default_triangles = new Vector3ui[_triangle_count];
					std::unique_ptr<Vector3ui> default_triangles_unique(default_triangles);

					// for each triangle, we generate 3 vertices, with 3 matching normals
					unsigned int vertex_index = 0;
					for (unsigned int i = 0; i < _triangle_count; ++i)
					{
						for (unsigned int j = 0; j < 3; ++j)
						{
							default_triangles[i][j] = vertex_index;
							default_vertices[vertex_index] = _vertices[_triangles[i][j]];

							Vector3<T> v0 = _vertices[_triangles[i][1]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());
							Vector3<T> v1 = _vertices[_triangles[i][2]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());

							default_normals[vertex_index] = v0.Cross(v1);
							vertex_index++;
						}
					}

					delete _triangles;
					delete _vertices;
					
					_triangles = default_triangles;
					default_triangles_unique.release();

					_vertices = default_vertices;
					_vertex_count = vertex_index;
					default_vertices_unique.release();

					_vertex_normals = default_normals;
					_vertex_normals_count = vertex_index;
					default_normals_unique.release();
				}
				// ensure that the count is correct
				else if (_vertex_count != _vertex_normals_count)
				{
					return false;
				}

				return true;
			}

			// vertices
            Vector4<T> * _vertices;
            unsigned int _vertex_count;

			// vertex normals
			Vector3<T> * _vertex_normals;
			unsigned int _vertex_normals_count;

			// vertex colors
			Vector4f * _vertex_colors;
			unsigned int _vertex_colors_count;

			// triangles
			Vector3ui * _triangles;
			unsigned int _triangle_count;

			// default vertex color
			static const Vector4f kDefaultVertexColor;
    };

	template <typename T>
	const Vector4f MeshType<T>::kDefaultVertexColor = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);

	typedef MeshType<float> Mesh;
	typedef MeshType<double> Meshd;
}

#endif // _mesh_h