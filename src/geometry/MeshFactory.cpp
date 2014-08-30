//
//  MeshFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 27/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "MeshFactory.hpp"
#include "utility/io.hpp"

#include <cstring>
#include <cstdlib>
#include <memory>

namespace Renderer
{
	const int MeshFactory::kObjSourceLineOffset = 2;

    Mesh * MeshFactory::MeshFromObjFile(const char * Obj_file_path)
    {
        if(Obj_file_path == nullptr)
        {
            return nullptr;
        }
        
        char * obj_source = IO::ReadFile(Obj_file_path);
		std::unique_ptr<char> obj_source_unique(obj_source);
        
		Mesh * mesh = MeshFactory::MeshFromObjSource(obj_source);
        
        return mesh;
    }
    
    Mesh * MeshFactory::MeshFromObjSource(char * Obj_source)
    {
        if(Obj_source == nullptr)
        {
            return nullptr;
        }     

		Mesh * mesh = new Mesh();

		std::vector<Vector4f> vertices;
		std::vector<Vector3ui> triangles;

        char * line = std::strtok(Obj_source, "\n");
        
        while(line != nullptr)
        {
			MeshFactory::AppendObjSourceLine(line, &vertices, &triangles);
            line = std::strtok(nullptr, "\n");
        }

		mesh->SetVertices(&vertices[0], static_cast<unsigned long>(vertices.size()));
		mesh->SetTriangles(&triangles[0], static_cast<unsigned long>(triangles.size()));

		return mesh;
    }

	void MeshFactory::AppendObjSourceLine(char * Obj_source_line,
										  std::vector<Vector4f> * vertices,
										  std::vector<Vector3ui> * triangles)
	{
		if (Obj_source_line[0] == 'v')
		{
			vertices->push_back(MeshFactory::VertexFromObjSource(Obj_source_line + kObjSourceLineOffset));
		}
		else if (Obj_source_line[0] == 'f')
		{			
			triangles->push_back(MeshFactory::TriangleFromObjSource(Obj_source_line + kObjSourceLineOffset));
		}
	}

	Vector4f MeshFactory::VertexFromObjSource(char * Obj_vertex_line)
	{
		Vector4f vertex;
		char * end = Obj_vertex_line;
		for (int i = 0; i<3; i++)
		{
			vertex[i] = strtof(end, &end);
		}

		vertex[3] = 1.0f;

		return vertex;
	}

	Vector3ui MeshFactory::TriangleFromObjSource(char * Obj_triangle_line)
	{
		Vector3ui triangle;
		char * end = Obj_triangle_line;
		for (int i = 0; i<3; i++)
		{
			triangle[i] = static_cast<unsigned int>(strtol(end, &end, 10)) - 1;
		}

		return triangle;
	}
}