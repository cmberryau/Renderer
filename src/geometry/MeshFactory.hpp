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
#include <vector>

namespace Renderer
{
    class MeshFactory
    {
        public:
            static Mesh * MeshFromObjFile(const char * obj_file_path);
            static Mesh * MeshFromObjSource(char * obj_source);
        
        protected:
			static void AppendObjSourceLine(char * obj_source_line,
														 std::vector<Vector4f> * vertices,
														 std::vector<Vector3ui> * faces);
			static Vector4f VertexFromObjSource(char * obj_vertex_line);
			static Vector3ui TriangleFromObjSource(char * obj_vertex_line);
			static const int kObjSourceLineOffset;

            MeshFactory(){};
            ~MeshFactory(){};
    };
}

#endif // _mesh_factory_h