//
//  Mesh.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _mesh_h
#define _mesh_h

#include "math/Vector.hpp"

#include <exception>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Renderer
{
	class Mesh
	{
		public:
			explicit Mesh() {}
			~Mesh() {}

			// validation
			void Validate();

			// vertex related
			void SetVertices(const std::vector<Vector4f> & vertices);			
			const std::vector<Vector4f> & VerticesVector() const;
			const Vector4f * const Vertices() const;
			std::size_t VerticesSize() const;
			std::size_t VertexCount() const;

			// vertex normal related
			void SetVertexNormals(const std::vector<Vector3f> & vertex_normals);    
			const std::vector<Vector3f> & VertexNormalsVector() const;
			const Vector3f * const VertexNormals() const;
			std::size_t VertexNormalsSize() const;
			std::size_t VertexNormalsCount() const;

			// vertex color related
			void SetColors(const std::vector<Vector4f> & vertex_colors);
			const std::vector<Vector4f> & ColorsVector() const;
			const Vector4f * const Colors() const;
			std::size_t ColorsSize() const;
			std::size_t ColorsCount() const;

			// uv related
			void SetUVs(const std::vector<Vector2f> & uvs);
			const std::vector<Vector2f> & UVsVector() const;
			const Vector2f * const UVs() const;
			std::size_t UVsSize() const;
			std::size_t UVsCount() const;

			// triangle related
			void SetTriangles(const std::vector<Vector3ui> & triangles);
			const std::vector<Vector3ui> & TrianglesVector() const;
			const Vector3ui * const Triangles() const;
			std::size_t TrianglesSize() const;
			std::size_t TrianglesCount() const;
		
			// debug output
			void Print() const;

		protected:
			void ValidateColors();
			void ValidateNormals();

			std::vector<Vector4f> _vertices;
			std::vector<Vector3f> _vertex_normals;
			std::vector<Vector4f> _vertex_colors;
			std::vector<Vector2f> _uvs;
			std::vector<Vector3ui> _triangles;

			// default vertex color
			static const Vector4f kDefaultVertexColor;
	};
}

#endif // _mesh_h