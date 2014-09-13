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
#include <locale>

namespace Renderer
{
    const int MeshFactory::kMaxVertexElements = 3;
    const int MeshFactory::kMaxNormalElements = 3;
    const int MeshFactory::kMaxUVElements = 2;
    
    void MeshFactory::ValidateIntermediateMesh(IntermediateMesh & intermediate_mesh)
    {
        if(intermediate_mesh.vertex_indices.size() <= 0)
        {
            throw std::exception();
        }
        
        if(intermediate_mesh.uv_indices.size() > 0)
        {
            if(intermediate_mesh.uv_indices.size() <
               intermediate_mesh.vertex_indices.size())
            {
                throw std::exception();
            }
            else if(intermediate_mesh.uv_indices.size() <
                    intermediate_mesh.vertex_indices.size())
            {
                throw std::exception();
            }
        }
        
        if(intermediate_mesh.normal_indices.size() > 0)
        {
            if(intermediate_mesh.normal_indices.size() <
               intermediate_mesh.vertex_indices.size())
            {
                throw std::exception();
            }
            else if(intermediate_mesh.normal_indices.size() <
                    intermediate_mesh.vertex_indices.size())
            {
                throw std::exception();
            }
        }
    }
    
    void MeshFactory::PrepareIntermediateMesh(IntermediateMesh & intermediate_mesh)
    {
        std::vector<Vector4f> vertices;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        
        std::vector<Vector3ui>::iterator it; int i = 0; int k = 0;
        for(it = intermediate_mesh.vertex_indices.begin();
            it != intermediate_mesh.vertex_indices.end(); ++it)
        {
            for(int j = 0; j < 3; j++)
            {
                vertices.push_back(intermediate_mesh.vertices[intermediate_mesh.vertex_indices[i][j]]);
                
                if(intermediate_mesh.normals.size() > 0)
                {
                    normals.push_back(intermediate_mesh.normals[intermediate_mesh.normal_indices[i][j]]);
                }
            
                if(intermediate_mesh.uvs.size() > 0)
                {
                    uvs.push_back(intermediate_mesh.uvs[intermediate_mesh.uv_indices[i][j]]);
                }
                
                intermediate_mesh.vertex_indices[i][j] = k;
                ++k;
            }
            ++i;
        }
        
        intermediate_mesh.vertices = vertices;
        intermediate_mesh.normals = normals;
        intermediate_mesh.uvs = uvs;
    }
    
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
        
        MeshFactory::ValidateIntermediateMesh(intermediate_mesh);
        MeshFactory::PrepareIntermediateMesh(intermediate_mesh);

		mesh->SetVertices(&intermediate_mesh.vertices[0],
        static_cast<unsigned int>(intermediate_mesh.vertices.size()));
        
		mesh->SetTriangles(&intermediate_mesh.vertex_indices[0],
        static_cast<unsigned int>(intermediate_mesh.vertex_indices.size()));
        
        if(intermediate_mesh.normals.size() != 0)
        {
            mesh->SetVertexNormals(&intermediate_mesh.normals[0],
            static_cast<unsigned int>(intermediate_mesh.normals.size()));
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
                intermediate_mesh.normals.push_back(
                MeshFactory::NormalFromObjSource(obj_source_line));
            }
            else if(obj_source_line[1] == 't')
            {
                // vertex uv coord
                intermediate_mesh.uvs.push_back(
                MeshFactory::UVFromObjSource(obj_source_line));
            }
            else if(obj_source_line[1] == ' ')
            {
                // vertex position
       			intermediate_mesh.vertices.push_back(
                MeshFactory::VertexFromObjSource(obj_source_line));
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
		for (it = elements.begin(), i = 0;
             (it != elements.end() && i < kMaxVertexElements);
             ++it)
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
		for (it = elements.begin(), i = 0;
             (it != elements.end() && i < kMaxNormalElements);
             ++it)
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
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_uv_line, ' ');
        
        Vector2f uv;
        
        std::vector<std::string>::iterator it; int i;
        for (it = elements.begin(), i = 0;
             (it != elements.end() && i < kMaxUVElements);
             ++it)
        {
            if(std::isdigit((*it)[0], loc) || (*it)[0] == '-')
            {
                uv[i] = std::stof(*it);
                ++i;
            }
        }
        
        return uv;
    }
    
	void MeshFactory::TriangleIndexFromObjSource(std::string & obj_triangle_line,
                                           IntermediateMesh & intermediate_mesh)
	{
        Vector3ui vertex_index; bool vertex_index_added = false;
        Vector3ui uv_index; bool uv_index_added = false;
        Vector3ui normal_index; bool normal_index_added = false;
        
        // we have a whole line e.g 'f 1/1/1 2/2/2 3/3/3', we split this into
        // 'f' '1/1/1' '2/2/2' '3/3/3' and go into the second loop
        std::locale loc;
        std::vector<std::string> elements = split_string(obj_triangle_line, ' ');
        std::vector<std::string>::iterator it; int i;
		for (it = elements.begin(), i = 0; it != elements.end(); ++it)
		{
            if(std::isdigit((*it)[0], loc))
            {
                // we have a group of 1-3 indexes '1/1/1', which we split again
                // according to the standard, the 0th element is the vertex
                // position index, the 1st is the uv position index the final
                // element is the normal index
                std::vector<std::string> sub_elements = split_string(*it, '/');
                std::vector<std::string>::iterator sub_it; int j;
                for (sub_it = sub_elements.begin(), j = 0;
                     sub_it != sub_elements.end(); ++sub_it)
                {
                    if((*sub_it).size() > 0)
                    {
                        unsigned int index = static_cast<unsigned int>(std::stoll(*sub_it) - 1);
                        
                        if(j == 0)
                        {
                            vertex_index[i] = index;
                            vertex_index_added = true;
                        }
                        else if(j == 1)
                        {
                            uv_index[i] = index;
                            uv_index_added = true;
                        }
                        else if(j == 2)
                        {
                            normal_index[i] = index;
                            normal_index_added = true;
                        }
                        // there should be no more than 3 elements
                        else
                        {
                            throw std::exception();
                        }
                    }
                    ++j;
                }
                ++i;
            }
        }
        
        // we got exactly 3 elements? we don't support non-triangles yet
        if(i != 3)
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