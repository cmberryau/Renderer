//
//  Mesh.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Mesh.hpp"

namespace Renderer
{
	const Vector4f Mesh::kDefaultVertexColor = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);

	void Mesh::Validate()
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
		try
		{
			ValidateNormals();
		}
		catch (std::exception)
		{
			std::cout << "Mesh normals incorrect" << std::endl;
		}

		// validate the vertex colors
		try
		{
			ValidateColors();
		}
		catch (std::exception)
		{
			std::cout << "Mesh colors incorrect" << std::endl;
		}
	}

	// vertex related
	void Mesh::SetVertices(const std::vector<Vector4f> & vertices)
	{
		_vertices.clear();
		_vertices = vertices;
	}

	const std::vector<Vector4f> & Mesh::VerticesVector() const
	{
		return _vertices;
	}

	const Vector4f * const Mesh::Vertices() const
	{
		return static_cast<const Vector4f *>(&_vertices[0]);
	}

	std::size_t Mesh::VerticesSize() const
	{
		return _vertices.size() * Vector4f::Size();
	}

	std::size_t Mesh::VertexCount() const
	{
		return _vertices.size();
	}

	// vertex normal related
	void Mesh::SetVertexNormals(const std::vector<Vector3f> & vertex_normals)
	{
		_vertex_normals.clear();
		_vertex_normals = vertex_normals;
	}

	const std::vector<Vector3f> & Mesh::VertexNormalsVector() const
	{
		return _vertex_normals;
	}

	const Vector3f * const Mesh::VertexNormals() const
	{
		return static_cast<const Vector3f *>(&_vertex_normals[0]);
	}

	std::size_t Mesh::VertexNormalsSize() const
	{
		return _vertex_normals.size() * Vector3f::Size();
	}

	std::size_t Mesh::VertexNormalsCount() const
	{
		return _vertex_normals.size();
	}

	// vertex color related
	void Mesh::SetColors(const std::vector<Vector4f> & vertex_colors)
	{
		_vertex_colors.clear();
		_vertex_colors = vertex_colors;
	}

	const std::vector<Vector4f> & Mesh::ColorsVector() const
	{
		return _vertex_colors;
	}

	const Vector4f * const Mesh::Colors() const
	{
		return static_cast<const Vector4f * const>(&_vertex_colors[0]);
	}

	std::size_t Mesh::ColorsSize() const
	{
		return _vertex_colors.size() * Vector4f::Size();
	}

	std::size_t Mesh::ColorsCount() const
	{
		return _vertex_colors.size();
	}

	// uv related
	void Mesh::SetUVs(const std::vector<Vector2f> & uvs)
	{
		_uvs.clear();
		_uvs = uvs;
	}

	const std::vector<Vector2f> & Mesh::UVsVector() const
	{
		return _uvs;
	}

	const Vector2f * const Mesh::UVs() const
	{
		return static_cast<const Vector2f *>(&_uvs[0]);
	}

	std::size_t Mesh::UVsSize() const
	{
		return _uvs.size() * Vector2f::Size();
	}

	std::size_t Mesh::UVsCount() const
	{
		return _uvs.size();
	}

	// triangle related
	void Mesh::SetTriangles(const std::vector<Vector3ui> & triangles)
	{
		_triangles.clear();
		_triangles = triangles;
	}

	const std::vector<Vector3ui> & Mesh::TrianglesVector() const
	{
		return _triangles;
	}

	const Vector3ui * const Mesh::Triangles() const
	{
		return static_cast<const Vector3ui *>(&_triangles[0]);
	}

	std::size_t Mesh::TrianglesSize() const
	{
		return _triangles.size() * Vector3ui::Size();
	}

	std::size_t Mesh::TrianglesCount() const
	{
		return _triangles.size();
	}

	// debug output
	void Mesh::Print() const
	{
		std::vector<Vector4f>::const_iterator it;
		for (it = _vertices.begin(); it != _vertices.end(); ++it)
		{
			(*it).Print();
		}
	}

	void Mesh::ValidateColors()
	{
		// if the mesh does not contain vertex colors, we assign default ones
		if (_vertex_colors.size() == 0)
		{
			std::vector<Vector4f>::iterator it;
			for (it = _vertices.begin(); it != _vertices.end(); ++it)
			{
				_vertex_colors.push_back(Mesh::kDefaultVertexColor);
			}
		}
		// there must be a color for each vertex
		else if (_vertices.size() != _vertex_colors.size())
		{
			throw std::exception();
		}
	}

	void Mesh::ValidateNormals()
	{
		// if the mesh does not contain vertex normals, we must assign some
		if (_vertex_normals.size() == 0)
		{
			// because we are not provided with any normals, we do not assume to smooth
			// or guess normals, this could confuse the user and provide unexpected results
			std::vector<Vector3f> default_normals;
			std::vector<Vector4f> default_vertices;
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

					Vector3f v0 = _vertices[_triangles[i][1]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());
					Vector3f v1 = _vertices[_triangles[i][2]].Vec3().Subtract(_vertices[_triangles[i][0]].Vec3());

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
			throw std::exception();
		}
	}
}