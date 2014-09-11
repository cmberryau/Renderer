//
//  MeshFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 27/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "MeshFactory.hpp"
#include "utility/io.hpp"
#include "utility/util.hpp"

#include <cstring>
#include <cstdlib>
#include <memory>
#include <iostream>

namespace Renderer
{
	const int MeshFactory::kObjSourceLineOffset = 2;
    
    Mesh * MeshFactory::MeshFromObjFile(std::string & obj_file_path)
    {        
        std::string obj_source = IO::ReadFile(obj_file_path);
        
		Mesh * mesh = MeshFactory::MeshFromObjSource(obj_source);
        
        return mesh;
    }
    
    Mesh * MeshFactory::MeshFromObjSource(std::string & obj_source)
    {
		Mesh * mesh = new Mesh();
        
		std::vector<Vector4f> intermediate_vertices;
        std::vector<Vector3f> intermediate_normals;
        std::vector<Vector2f> intermediate_uvs;
		std::vector<Vector3ui> triangles;
        
        std::vector<std::string> lines = split_string(obj_source, '\n');
        
        std::vector<std::string>::iterator it;
        for(it = lines.begin(); it != lines.end(); ++it)
        {
			MeshFactory::AppendObjSourceLine(*it,
                                             intermediate_vertices,
                                             intermediate_normals,
                                             intermediate_uvs,
                                             triangles);
        }
        
        if(intermediate_vertices.size() == 0 || triangles.size() == 0)
        {
            throw std::exception();
        }
        
		mesh->SetVertices(&intermediate_vertices[0], static_cast<unsigned long>(intermediate_vertices.size()));
		mesh->SetTriangles(&triangles[0], static_cast<unsigned long>(triangles.size()));
        
        if(intermediate_normals.size() != 0)
        {
            //mesh->SetVertexNormals(&normals[0], static_cast<unsigned long>(normals.size()));
        }
        
        if(intermediate_uvs.size() != 0 )
        {
            
        }
        
		return mesh;
    }
    
	void MeshFactory::AppendObjSourceLine(std::string & obj_source_line,
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
       			vertices.push_back(MeshFactory::VertexFromObjSource(obj_source_line));
            }
            else
            {
                throw std::exception();
            }
		}
		else if (obj_source_line[0] == 'f')
		{
			triangles.push_back(MeshFactory::TriangleFromObjSource(obj_source_line));
		}
	}
    
	Vector4f MeshFactory::VertexFromObjSource(std::string & obj_vertex_line)
	{
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_vertex_line, ' ');
        
		Vector4f vertex;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it)
		{
            if(std::isdigit((*it)[0], loc) || (*it)[0] == '-')
            {
                vertex[i] = std::stof(*it);
                ++i;
            }
		}
        
		vertex[3] = 1.0f;
        
		return vertex;
	}
    
    Vector3f MeshFactory::NormalFromObjSource(std::string & obj_normal_line)
    {
        std::vector<std::string> elements = split_string(obj_normal_line, ' ');
        
        Vector3f normal;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it, ++i)
		{
			//normal[i] = strtof(end, &end);
		}
        
		return normal;
    }
    
    Vector2f MeshFactory::UVFromObjSource(std::string & obj_uv_line)
    {
        std::vector<std::string> elements = split_string(obj_uv_line, ' ');
        
        Vector2f uv;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it, ++i)
		{
			//uv[i] = strtof(end, &end);
		}
        
        return uv;
    }
    
	Vector3ui MeshFactory::TriangleFromObjSource(std::string & obj_triangle_line)
	{
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_triangle_line, ' ');
        
		Vector3ui triangle;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it)
		{
            if(std::isdigit((*it)[0], loc))
            {
                std::vector<std::string> sub_elements = split_string(*it, '\\');
                std::vector<std::string>::iterator sub_it; int j;
                for (sub_it = sub_elements.begin(), j = 0; sub_it != sub_elements.end(); ++sub_it)
                {
                    if(j == 0)
                    {
                        triangle[i] = static_cast<unsigned int>(std::stoll(*it) - 1);
                    }
                    ++j;
                }
                ++i;
            }
        }
        
		return triangle;
	}
}