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

namespace Renderer
{
    Mesh * MeshFactory::MeshFromOBJFile(const char * obj_file_path)
    {
        if(obj_file_path == nullptr)
        {
            return nullptr;
        }
        
        char * obj_source = IO::ReadFile(obj_file_path);
        
        Mesh * mesh = MeshFactory::MeshFromOBJSource(obj_source);
        
        return mesh;
    }
    
    Mesh * MeshFactory::MeshFromOBJSource(char * obj_source)
    {
        if(obj_source == nullptr)
        {
            return nullptr;
        }
        
        char * line = std::strtok(obj_source, " ");
        
        int vertex_count = 0;
        int face_count = 0;
        
        while(line != nullptr)
        {
            // it's a vertex
            if(line[0] == 'v')
            {
                for(int i=0; i<3; i++)
                {
                    //line = std::strtok(nullptr, " \n");
                }
                
                vertex_count++;
            }
            // it's a face
            else if(line[0] == 'f')
            {
                face_count++;
                //line = std::strtok(nullptr, "\n");
            }
            
            line = std::strtok(nullptr, "\n");
        }
        
        fprintf(stdout, "vertex count: %d, face count: %d\n", vertex_count, face_count);
        
        return nullptr;
    }
}