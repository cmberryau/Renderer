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

// OpenGL includes
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <SDL2/SDL_opengl.h>
#include <exception>

namespace Renderer
{
	class OpenGLMeshRenderer : public MeshRenderer
	{
		public:
			explicit OpenGLMeshRenderer(RenderingContext * rendering_context);
            explicit OpenGLMeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr);
			virtual ~OpenGLMeshRenderer();

			virtual void AddMesh(Mesh * mesh) override;
            virtual void AddMesh(const std::shared_ptr<Mesh> & mesh_ptr) override;
        
			virtual void Draw(Object * parent_object) const override;
            virtual void Draw(const Object & parent_object) const override;
		
        protected:
            void GenerateArrays(const Mesh * mesh);
            void CreateShader(const Mesh * mesh);
        
            void GenerateArrays(const Mesh & mesh);
            void CreateShader(const Mesh & mesh);
        
            static bool CheckForGLError();
        
		private:
			GLuint _vertex_array_objects[1];
			GLuint _vertex_element_buffer[1];
			GLuint _vertex_buffer_objects[1];
		
			GLint _model_matrix_uniform;
			GLint _normal_matrix_uniform;
			GLint _projection_matrix_uniform;
	};
}

#endif // _opengl_mesh_renderer_h

#endif // !EMSCRIPTEN