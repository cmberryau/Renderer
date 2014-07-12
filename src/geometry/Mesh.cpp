//
//  Mesh.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Mesh.h"
#include <stdio.h>

namespace Renderer
{
	// factory constructor
	Mesh * Mesh::Create(Vector3f * vertices, unsigned int size)
	{
		// confirm the passed data
		if (vertices == nullptr)
			return nullptr;

		Mesh * mesh = new Mesh();

		mesh->_vertices = new Vector3f[size];

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

	// vertex related
	void Mesh::SetVertices(Vector3f * vertices, unsigned int size)
	{
		this->_vertices = new Vector3f[size];

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

    const Vector3f * Mesh::Vertices()
    {
        return (const Vector3f *)_vertices;
    }
    
    unsigned int Mesh::VerticesSize()
    {
        return _vertices_count * Vector3f::Size();
    }
    
    unsigned int Mesh::VerticesCount()
    {
        return _vertices_count;
    }

	// vertex color related
	void Mesh::SetColors(Vector4f * vertex_colors, unsigned int size)
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

	const Vector4f * Mesh::Colors()
	{
		return (const Vector4f *)_vertex_colors;
	}

	unsigned int Mesh::ColorsSize()
	{
		return _vertex_colors_count * Vector4f::Size();
	}

	unsigned int Mesh::ColorsCount()
	{
		return _vertex_colors_count;
	}

	// triangle related
	void Mesh::SetTriangles(Vector3ui * triangles, unsigned int size)
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

	const Vector3ui * Mesh::Triangles()
	{
		return (const Vector3ui *)_triangles;
	}

	unsigned int Mesh::TrianglesSize()
	{
		return _triangles_count * Vector3ui::Size();
	}

	unsigned int Mesh::TrianglesCount()
	{
		return _triangles_count;
	}
    
	void Mesh::Print()
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

	Mesh::Mesh() : _vertices(nullptr), _vertices_count(0),
				   _vertex_colors(nullptr), _vertex_colors_count(0),
				   _triangles(nullptr), _triangles_count(0)
    {
        
    }
    
    Mesh::~Mesh()
    {
		delete _vertices;
		delete _vertex_colors;
		delete _triangles;
    }
}