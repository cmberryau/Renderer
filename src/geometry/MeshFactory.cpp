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
        
        IntermediateMesh intermediate_mesh;
        
        std::vector<std::string> lines = split_string(obj_source, '\n');
        
        std::vector<std::string>::iterator it;
        for(it = lines.begin(); it != lines.end(); ++it)
        {
			MeshFactory::AppendObjSourceLine(*it, intermediate_mesh);
        }
        
        if(intermediate_mesh.vertices.size() == 0 ||
           intermediate_mesh.vertex_indices.size() == 0)
        {
            throw std::exception();
        }
        
		mesh->SetVertices(&intermediate_mesh.vertices[0],
                          static_cast<unsigned int>(intermediate_mesh.vertices.size()));
        
		mesh->SetTriangles(&intermediate_mesh.vertex_indices[0],
                           static_cast<unsigned int>(intermediate_mesh.vertex_indices.size()));
        
        if(intermediate_mesh.normals.size() != 0)
        {
            //mesh->SetVertexNormals(&intermediate_mesh.normals[0],
            //                       static_cast<unsigned long>(intermediate_mesh.normals.size()));
        }
        
        if(intermediate_mesh.uvs.size() != 0 )
        {
            
        }
        
		return mesh;
    }
    
	void MeshFactory::AppendObjSourceLine(std::string & obj_source_line,
										  IntermediateMesh & intermediate_mesh)
	{
		if (obj_source_line[0] == 'v')
		{
            if (obj_source_line[1] == 'n')
            {
                // vertex normal
                intermediate_mesh.normals.push_back(MeshFactory::NormalFromObjSource(obj_source_line));
            }
            else if(obj_source_line[1] == 't')
            {
                // vertex uv coord
                //uvs.push_back(MeshFactory::UVFromObjSource(obj_source_line + kObjSourceLineOffset + 1));
            }
            else if(obj_source_line[1] == ' ')
            {
                // vertex position
       			intermediate_mesh.vertices.push_back(MeshFactory::VertexFromObjSource(obj_source_line));
            }
            else
            {
                throw std::exception();
            }
		}
		else if (obj_source_line[0] == 'f')
		{
			MeshFactory::TriangleIndexFromObjSource(obj_source_line, intermediate_mesh);
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
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_normal_line, ' ');
        
        Vector3f normal;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it, ++i)
		{
            if(std::isdigit((*it)[0], loc) || (*it)[0] == '-')
            {
                normal[i] = std::stof(*it);
                ++i;
            }
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
    
	void MeshFactory::TriangleIndexFromObjSource(std::string & obj_triangle_line,
                                                 IntermediateMesh & intermediate_mesh)
	{
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_triangle_line, ' ');
        
        Vector3ui vertex_index;
        Vector3ui uv_index;
        Vector3ui normal_index;
        
        bool vertex_index_added = false;
        bool uv_index_added = false;
        bool normal_index_added = false;
        
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it)
		{
            if(std::isdigit((*it)[0], loc))
            {
                std::vector<std::string> sub_elements = split_string(*it, '/');
                //std::cout << "Splits: " << sub_elements.size() << std::endl;
                std::vector<std::string>::iterator sub_it; int j;
                for (sub_it = sub_elements.begin(), j = 0; sub_it != sub_elements.end(); ++sub_it)
                {
                    //std::cout << " [" << j << "]" << " " << ((*sub_it).size() > 0 ? *sub_it : "NaN");
                    
                    if((*sub_it).size() > 0)
                    {
                        // the first value is always the vertex index
                        if(j == 0)
                        {
                            vertex_index[i] = static_cast<unsigned int>(std::stoll(*it) - 1);
                            vertex_index_added = true;
                        }
                        // the second value should be a texture coord index
                        else if(j == 1)
                        {
                            uv_index[i] = static_cast<unsigned int>(std::stoll(*it) - 1);
                            uv_index_added = true;
                        }
                        // the third value should be a vertex normal index
                        else if(j == 2)
                        {
                            normal_index[i] = static_cast<unsigned int>(std::stoll(*it) - 1);
                            normal_index_added = true;
                        }
                        // anything else is most likely in error
                        else
                        {
                            throw std::exception();
                        }
                    }
                    ++j;
                }
                //std::cout << std::endl;
                ++i;
            }
        }
        
        // we have more than 2 elements, right?
        if(i < 2)
        {
            throw std::exception();
        }
        
        if(vertex_index_added)
        {
            intermediate_mesh.vertex_indices.push_back(vertex_index);
        }
        
        if(uv_index_added)
        {
            intermediate_mesh.uv_indices.push_back(uv_index);
        }
        
        if(normal_index_added)
        {
            intermediate_mesh.normal_indices.push_back(normal_index);
        }
	}
}