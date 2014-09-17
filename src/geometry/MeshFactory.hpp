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
    struct IntermediateMesh
    {
        std::vector<Vector4f> vertices;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        
        std::vector<Vector3ui> vertex_indices;
        std::vector<Vector3ui> uv_indices;
        std::vector<Vector3ui> normal_indices;
    };
    
    class MeshFactory
    {
        public:
            static Mesh * MeshFromObjFile(std::string & obj_file_path);
            static Mesh * MeshFromObjSource(std::string & obj_source);
        
        protected:
            static void ValidateIntermediateMesh(IntermediateMesh & intermediate_mesh);
            static void PrepareIntermediateMesh(IntermediateMesh & intermediate_mesh);
        
			static void AppendObjSourceLine(std::string & obj_source_line,
                                            IntermediateMesh & intermediate_mesh);
        
			static Vector4f VertexFromObjSource(std::string & obj_vertex_line);
            static Vector3f NormalFromObjSource(std::string & obj_normal_line);
            static Vector2f UVFromObjSource(std::string & obj_uv_line);
			static void TriangleIndexFromObjSource(std::string & obj_vertex_line,
                                                   IntermediateMesh & intermediate_mesh);
        
            static const int kMaxVertexElements;
			static const int kMaxNormalElements;
            static const int kMaxUVElements;

            MeshFactory(){};
            ~MeshFactory(){};
    };
}

#endif // _mesh_factory_h