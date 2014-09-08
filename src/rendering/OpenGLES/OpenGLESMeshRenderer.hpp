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

namespace Renderer
{
    template <typename T>
	class OpenGLESMeshRendererType : public MeshRendererType<T>
	{
		public:
			static OpenGLESMeshRendererType<T> * Create(RenderingContext * rendering_context)
            {
                return new OpenGLESMeshRendererType<T>(rendering_context);
            }
        
			void SetMesh(MeshType<T> * mesh)
			{
				if (mesh == nullptr)
				{
					throw std::exception();
				}

				mesh->Validate();
				this->_mesh = mesh;

				this->GenerateArrays(mesh);
				this->CreateShader(mesh);
				this->CreateShader(mesh);				
			}

			void GenerateArrays(MeshType<float> * mesh)
			{
				glGenBuffers(1, &_vertex_position_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_position_buffer);
				glBufferData(GL_ARRAY_BUFFER, mesh->VerticesSize(), mesh->Vertices(), GL_STATIC_DRAW);

				glGenBuffers(1, &_vertex_normal_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_normal_buffer);
				glBufferData(GL_ARRAY_BUFFER, mesh->VertexNormalsSize(), mesh->VertexNormals(), GL_STATIC_DRAW);

				glGenBuffers(1, &_vertex_color_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_color_buffer);
				glBufferData(GL_ARRAY_BUFFER, mesh->ColorsSize(), mesh->Colors(), GL_STATIC_DRAW);

				glGenBuffers(1, &_triangle_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->TrianglesSize(), mesh->Triangles(), GL_STATIC_DRAW);
			}

            void CreateShader(MeshType<float> * mesh)
            {   
				this->_material->Use();

				glBindBuffer(GL_ARRAY_BUFFER, _vertex_position_buffer);
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, _vertex_normal_buffer);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, _vertex_color_buffer);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(2);

				OpenGLESShader * opengles_shader = dynamic_cast<OpenGLESShader *>(this->_material->Shader());

				_model_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "model_matrix");
				_projection_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "projection_matrix");
            }
        
			void Draw(ObjectType<float> * parent_object)
			{
				if (this->_mesh == nullptr)
				{
					throw std::exception();
				}

				this->_material->Use();

				glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, this->_rendering_context->MainCamera()->ProjectionMatrix());
				glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, parent_object->LocalTransform()->ComposedMatrix().Multiply(this->_rendering_context->MainCamera()->ViewMatrix()));

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
				glDrawElements(GL_TRIANGLES, this->_mesh->TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
			}

			~OpenGLESMeshRendererType<T>()
            {
                
            }

            OpenGLESMeshRendererType<T>(RenderingContextType<T> * rendering_context) : MeshRendererType<T>(rendering_context)
            {
                
            }

		protected:
			GLuint _vertex_position_buffer;
			GLuint _vertex_normal_buffer;
			GLuint _vertex_color_buffer;
			GLuint _triangle_index_buffer;

			GLint _model_matrix_uniform;
			GLint _projection_matrix_uniform;
	};
    
    typedef OpenGLESMeshRendererType<float> OpenGLESMeshRenderer;
    typedef OpenGLESMeshRendererType<double> OpenGLESMeshRendererd;
}

#endif // _opengles_mesh_renderer_h

#endif