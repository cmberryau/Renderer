//
//  OpenGLMeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#ifndef _opengl_mesh_renderer_h
#define _opengl_mesh_renderer_h

#include "rendering/MeshRenderer.hpp"
#include "rendering/Camera.hpp"
#include "rendering/OpenGL/OpenGLShader.hpp"
#include "rendering/OpenGL/OpenGLCommon.hpp"

#include <exception>

namespace Renderer
{
	class OpenGLMeshRenderer : public MeshRenderer
	{
		public:
            explicit OpenGLMeshRenderer();
			virtual ~OpenGLMeshRenderer();

            virtual void AddMesh(std::shared_ptr<Mesh> mesh_ptr) override;
            virtual void Draw(Object & parent_object, const Scene & scene) const override;
		
        protected:
            void GenerateArrays(const Mesh & mesh);
            void CreateShader(const Mesh & mesh);
        
		private:
			GLuint _vertex_array_objects;
			GLuint _vertex_element_buffer;
			GLuint _vertex_buffer_objects;
		
			GLint _model_matrix_uniform;
			GLint _normal_matrix_uniform;
			GLint _projection_matrix_uniform;
	};
}

#endif // _opengl_mesh_renderer_h

#endif // !EMSCRIPTEN