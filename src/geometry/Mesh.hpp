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
#include <vector>
#include <iostream>

namespace Renderer
{
	template <typename T>
	class MeshType
	{
		public:
			MeshType<T>()
			{

			}

			~MeshType<T>()
			{
				
			}
		
			void Validate()
			{
				// as a baseline, meshes must contain vertices and triangles
				// if the mesh is missing normals, we will calculate them
				if (_vertices.size() == 0 || _triangles.size() == 0)
				{
					throw std::exception();
				}

				// the triangle references must not be outside the vertex buffer
				std::vector<Vector3ui>::iterator it;
				for (it = _triangles.begin(); it != _triangles.end(); ++it)
				{
					for (int j = 0; j < 3; j++)
					{
						if ((*it)[j] > _vertices.size() - 1)
						{
							throw std::exception();
						}
					}
				}

				// validate normals
				if (!ValidateNormals())
				{
					std::cout << "ValidateNormals\n";
					throw std::exception();
				}

				// validate the vertex colors
				if (!ValidateColors())
				{
					std::cout << "ValidateColors\n";
					throw std::exception();
				}
			}

			// vertex related
			void SetVertices(Vector4<T> * vertices, unsigned int size)
			{
				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertices[i] == nullptr)
					{
						throw std::exception();
					}

					_vertices.push_back(vertices[i]);
				}
			}

			const Vector4<T> * Vertices()
			{
				return static_cast<const Vector4<T> *>(&_vertices[0]);
			}

			unsigned int VerticesSize()
			{
				return _vertices.size() * Vector4<T>::Size();
			}

			unsigned int VertexCount()
			{
				return _vertices.size();
			}

			// vertex normal related
			void SetVertexNormals(Vector3<T> * vertex_normals, unsigned int size)
			{
				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertex_normals[i] == nullptr)
					{
						throw std::exception();
					}

					_vertex_normals.push_back(vertex_normals[i]);
				}
			}
			
			const Vector3<T> * VertexNormals()
			{
				return static_cast<const Vector3<T> *>(&_vertex_normals[0]);
			}

			unsigned int VertexNormalsSize()
			{
				return _vertex_normals.size() * Vector3<T>::Size();
			}

			unsigned int VertexNormalsCount()
			{
				return _vertex_normals.size();
			}

			// vertex color related
			void SetColors(Vector4f * vertex_colors, unsigned int size)
			{
				for (unsigned int i = 0; i < size; ++i)
				{
					if (vertex_colors[i] == nullptr)
					{
						throw std::exception();
					}

					_vertex_colors.push_back(vertex_colors[i]);
				}
			}

			const Vector4f * Colors()
			{
				return static_cast<const Vector4f *>(&_vertex_colors[0]);
			}

			unsigned int ColorsSize()
			{
				return _vertex_colors.size() * Vector4f::Size();
			}

			unsigned int ColorsCount()
			{
				return _vertex_colors.size();
			}

			// triangle related
			void SetTriangles(Vector3ui * triangles, unsigned int size)
			{
				for (unsigned int i = 0; i < size; ++i)
				{
					if (triangles[i] == nullptr)
					{
						std::exception();
					}

					_triangles.push_back(triangles[i]);
				}
			}

			const Vector3ui * Triangles()
			{
				return static_cast<const Vector3ui *>(&_triangles[0]);
			}

			unsigned int TrianglesSize()
			{
				return _triangles.size() * Vector3ui::Size();
			}

			unsigned int TrianglesCount()
			{
				return _triangles.size();
			}
		
			// debug output
			void Print()
			{
				for (unsigned int i = 0; i < _vertices.size(); ++i)
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
				if (_vertex_colors.size() == 0)
				{
					for (unsigned int i = 0; i < _vertices.size(); ++i)
					{
						_vertex_colors.push_back(MeshType<T>::kDefaultVertexColor);
					}
				}
				// there must be a color for each vertex
				else if (_vertices.size() != _vertex_colors.size())  
				{
					throw std::exception();
				}

				return true;
			}

			bool ValidateNormals()
			{
				// if the mesh does not contain vertex normals, we must assign some
				if (_vertex_normals.size() == 0)
				{
					// because we are not provided with any normals, we do not assume to smooth
					// or guess normals, this could confuse the user and provide unexpected results
					std::vector<Vector3<T>> default_normals;			
					std::vector<Vector4<T>> default_vertices;
					std::vector<Vector3ui> default_triangles;

					// for each triangle, we generate 3 vertices, with 3 matching normals
					unsigned int vertex_index = 0;
					for (unsigned int i = 0; i < _triangles.size(); ++i)
					{
						default_triangles.push_back(Vector3ui(0));
						for (unsigned int j = 0; j < 3; ++j)
						{
							default_triangles[i][j] = vertex_index;
							default_vertices.push_back(_vertices[_triangles[i][j]]);

							Vector3<T> v0 = _vertices[_triangles[i][1]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());
							Vector3<T> v1 = _vertices[_triangles[i][2]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());

							default_normals.push_back(v0.Cross(v1));
							vertex_index++;
						}
					}
					
					_triangles = default_triangles;
					_vertices = default_vertices;
					_vertex_normals = default_normals;
				}
				// ensure that the count is correct
				else if (_vertices.size() != _vertex_normals.size())
				{
					return false;
				}

				return true;
			}

			// vertices
			std::vector <Vector4<T>> _vertices;

			// vertex normals
			std::vector<Vector3<T>> _vertex_normals;

			// vertex colors
			std::vector<Vector4f> _vertex_colors;

			// triangles
			std::vector<Vector3ui> _triangles;

			// default vertex color
			static const Vector4f kDefaultVertexColor;
	};

	template <typename T>
	const Vector4f MeshType<T>::kDefaultVertexColor = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);

	typedef MeshType<float> Mesh;
	typedef MeshType<double> Meshd;
}

#endif // _mesh_h