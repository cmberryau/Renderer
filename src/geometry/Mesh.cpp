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

	Mesh::Mesh() : _vertices(nullptr)
    {
        
    }
    
    Mesh::~Mesh()
    {
		delete _vertices;
    }
}