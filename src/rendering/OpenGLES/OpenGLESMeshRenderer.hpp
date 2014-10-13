//
//  OpenGLESMeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 04/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#ifndef _opengles_mesh_renderer_h
#define _opengles_mesh_renderer_h

#include "rendering/MeshRenderer.hpp"
#include "rendering/Camera.hpp"
#include "rendering/OpenGLES/OpenGLESShader.hpp"
#include "rendering/OpenGLES/OpenGLESCommon.hpp"

#include <iostream>

namespace Renderer
{
	class OpenGLESMeshRenderer : public MeshRenderer
	{
        public:
            explicit OpenGLESMeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr);
            virtual ~OpenGLESMeshRenderer();
            
            virtual void AddMesh(const std::shared_ptr<Mesh> & mesh_ptr) override;
            virtual void Draw(Object & parent_object, const Scene & scene) const override;
            
        protected:
            void GenerateArrays(const Mesh & mesh);
            void CreateShader(const Mesh & mesh);

		private:
			GLuint _vertex_position_buffer;
			GLuint _vertex_normal_buffer;
			GLuint _vertex_color_buffer;
			GLuint _triangle_index_buffer;

			GLint _model_matrix_uniform;
            GLint _normal_matrix_uniform;
			GLint _projection_matrix_uniform;
	};
}

#endif // _opengles_mesh_renderer_h

#endif