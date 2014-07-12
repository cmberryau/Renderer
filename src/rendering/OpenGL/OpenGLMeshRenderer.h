//
//  OpenGLMeshRenderer.h
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_mesh_renderer_h
#define _opengl_mesh_renderer_h

#include "rendering/MeshRenderer.h"

namespace Renderer
{
	class OpenGLMeshRenderer : public MeshRenderer
	{
		public:
            static OpenGLMeshRenderer * Create();
            void Store(Mesh * mesh);
			void Draw(Object * parent_object);
        
			~OpenGLMeshRenderer();

		protected:
   			OpenGLMeshRenderer();
        
            RenderingContext * _rendering_context;
        
            GLuint _vertex_array_objects[1];
			GLuint _vertex_element_buffer[1];
            GLuint _vertex_buffer_objects[1];
        
            GLuint _shader_program;
            GLint _model_matrix_uniform;
            GLint _projection_matrix_uniform;
	};
}

#endif // #ifndef _opengl_mesh_renderer_h