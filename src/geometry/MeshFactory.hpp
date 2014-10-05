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
            static Mesh * MeshFromObjFile(const std::string & obj_file_path);
			static Mesh * MeshFromObjSource(const std::string & obj_source);
        
        protected:
            static void ValidateIntermediateMesh(const IntermediateMesh & intermediate_mesh);
            static void PrepareIntermediateMesh(IntermediateMesh & intermediate_mesh);
        
			static void AppendObjSourceLine(const std::string & obj_source_line,
                                            IntermediateMesh & intermediate_mesh);
        
			static Vector4f VertexFromObjSource(const std::string & obj_vertex_line);
			static Vector3f NormalFromObjSource(const std::string & obj_normal_line);
            static Vector2f UVFromObjSource(const std::string & obj_uv_line);
			static void TriangleIndexFromObjSource(const std::string & obj_vertex_line,
                                                   IntermediateMesh & intermediate_mesh);
        
            static const int kMaxVertexElements = 3;
			static const int kMaxNormalElements = 3;
            static const int kMaxUVElements = 2;

            explicit MeshFactory(){};
            ~MeshFactory(){};
    };
}

#endif // _mesh_factory_h