//
//  MeshFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 27/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_factory_h
#define _mesh_factory_h

#include "Mesh.hpp"

namespace Renderer
{
    class MeshFactory
    {
        public:
            static Mesh * MeshFromOBJFile(const char * obj_file_path);
            static Mesh * MeshFromOBJSource(char * obj_source);
        
        protected:
            MeshFactory(){};
            ~MeshFactory(){};
    };
}

#endif // _mesh_factory_h