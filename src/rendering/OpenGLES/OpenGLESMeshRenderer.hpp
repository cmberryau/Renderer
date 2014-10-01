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

#include <SDL2/SDL_opengles2.h>
#include <iostream>

namespace Renderer
{
	class OpenGLESMeshRenderer : public MeshRenderer
	{
		public:
			~OpenGLESMeshRenderer();

			explicit OpenGLESMeshRenderer(RenderingContext * rendering_context);
        
			void SetMesh(Mesh * mesh);
			void GenerateBuffers(Mesh * mesh);
			void SetupShader(Mesh * mesh);        
			void Draw(Object * parent_object);

		protected:
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