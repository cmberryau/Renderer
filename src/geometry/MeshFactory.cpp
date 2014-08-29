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
        
        char * line = std::strtok(obj_source, "\n");
        
        while(line != nullptr)
        {
            // it's a vertex
            if(line[0] == 'v' || line[0] == 'f')
            {
                size_t span_to_space = 0;
                // one space after the first value notifing what the type is
                char * seeked_pos = line + 2;
                for(int i=0; i<3; i++)
                {
                    span_to_space = strcspn(seeked_pos, " \n");
                    float value = strtod(seeked_pos, &seeked_pos + span_to_space);
                    
                    seeked_pos += span_to_space + 1;
                }
            }
            
            line = std::strtok(nullptr, "\n");
        }
        
        return nullptr;
    }
}