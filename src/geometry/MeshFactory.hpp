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
#include <string>
#include <sstream>

namespace Renderer
{
    class MeshFactory
    {
        public:
            static Mesh * MeshFromObjFile(std::string & obj_file_path);
            static Mesh * MeshFromObjSource(std::string & obj_source);
        
        protected:        
			static void AppendObjSourceLine(std::string &obj_source_line,
                                            std::vector<Vector4f> & vertices,
                                            std::vector<Vector3f> & normals,
                                            std::vector<Vector2f> & uvs,
                                            std::vector<Vector3ui> & faces);
        
			static Vector4f VertexFromObjSource(std::string & obj_vertex_line);
            static Vector3f NormalFromObjSource(std::string & obj_normal_line);
            static Vector2f UVFromObjSource(std::string & obj_uv_line);
			static Vector3ui TriangleFromObjSource(std::string & obj_vertex_line);
        
			static const int kObjSourceLineOffset;

            MeshFactory(){};
            ~MeshFactory(){};
    };
}

#endif // _mesh_factory_h