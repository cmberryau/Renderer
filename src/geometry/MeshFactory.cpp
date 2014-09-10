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
    
    Mesh * MeshFactory::MeshFromObjFile(const char * obj_file_path)
    {
        if(obj_file_path == nullptr)
        {
            return nullptr;
        }
        
        char * obj_source = IO::ReadFile(obj_file_path);
		std::unique_ptr<char> obj_source_unique(obj_source);
        
		Mesh * mesh = MeshFactory::MeshFromObjSource(obj_source);
        
        return mesh;
    }
    
    Mesh * MeshFactory::MeshFromObjSource(char * obj_source)
    {
        if(obj_source == nullptr)
        {
            return nullptr;
        }
        
		Mesh * mesh = new Mesh();
        
		std::vector<Vector4f> vertices;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
		std::vector<Vector3ui> triangles;
        
        char * line = std::strtok(obj_source, "\n");
        
        while(line != nullptr)
        {
			MeshFactory::AppendObjSourceLine(line, vertices, normals, uvs, triangles);
            line = std::strtok(nullptr, "\n");
        }
        
        if(vertices.size() == 0 || triangles.size() == 0)
        {
            throw std::exception();
        }
        
		mesh->SetVertices(&vertices[0], static_cast<unsigned long>(vertices.size()));
		mesh->SetTriangles(&triangles[0], static_cast<unsigned long>(triangles.size()));
        
        if(normals.size() != 0)
        {
            mesh->SetVertexNormals(&normals[0], static_cast<unsigned long>(normals.size()));
        }
        
        if(uvs.size() != 0 )
        {
            
        }
        
		return mesh;
    }
    
	void MeshFactory::AppendObjSourceLine(char * obj_source_line,
										  std::vector<Vector4f> & vertices,
                                          std::vector<Vector3f> & normals,
                                          std::vector<Vector2f> & uvs,
										  std::vector<Vector3ui> & triangles)
	{
		if (obj_source_line[0] == 'v')
		{
            if (obj_source_line[1] == 'n')
            {
                // vertex normal
                //normals.push_back(MeshFactory::NormalFromObjSource(obj_source_line + kObjSourceLineOffset + 1));
            }
            else if(obj_source_line[1] == 't')
            {
                // vertex uv coord
                //uvs.push_back(MeshFactory::UVFromObjSource(obj_source_line + kObjSourceLineOffset + 1));
            }
            else if(obj_source_line[1] == ' ')
            {
                // vertex position
       			vertices.push_back(MeshFactory::VertexFromObjSource(obj_source_line + kObjSourceLineOffset));
            }
            else
            {
                throw std::exception();
            }
		}
		else if (obj_source_line[0] == 'f')
		{
			triangles.push_back(MeshFactory::TriangleFromObjSource(obj_source_line + kObjSourceLineOffset));
		}
	}
    
	Vector4f MeshFactory::VertexFromObjSource(char * obj_vertex_line)
	{
		Vector4f vertex;
		char * end = obj_vertex_line;
		for (int i = 0; i<3; i++)
		{
			vertex[i] = strtof(end, &end);
		}
        
		vertex[3] = 1.0f;
        
		return vertex;
	}
    
    Vector3f MeshFactory::NormalFromObjSource(char * obj_normal_line)
    {
        Vector3f normal;
        char * end = obj_normal_line;
		for (int i = 0; i<3; i++)
		{
			normal[i] = strtof(end, &end);
		}
        
		return normal;
    }
    
    Vector2f MeshFactory::UVFromObjSource(char * obj_uv_line)
    {
        Vector2f uv;
        char * end = obj_uv_line;
        
		for (int i = 0; i<2; i++)
		{
			uv[i] = strtof(end, &end);
		}
        
        return uv;
    }
    
	Vector3ui MeshFactory::TriangleFromObjSource(char * obj_triangle_line)
	{
		Vector3ui triangle;
		char * end = obj_triangle_line;
        
		for (int i = 0; i<3; i++)
		{
			triangle[i] = static_cast<unsigned int>(strtol(end, &end, 10)) - 1;
            
            end = strchr(end, ' ');
        }
        
		return triangle;
	}
}