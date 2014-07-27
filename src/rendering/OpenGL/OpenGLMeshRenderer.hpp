//
//  OpenGLMeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _opengl_mesh_renderer_h
#define _opengl_mesh_renderer_h

#include "rendering/MeshRenderer.hpp"
#include "utility/LoadShaders.h"
#include "rendering/Camera.hpp"

namespace Renderer
{
    template <typename T>
	class OpenGLMeshRendererType : public MeshRendererType<T>
	{
		public:
			static OpenGLMeshRendererType<T> * Create(RenderingContext * rendering_context)
            {
                return new OpenGLMeshRendererType<T>(rendering_context);
            }
        
			void Store(MeshType<T> * mesh)
			{
				if (mesh == nullptr)
				{
					// todo : throw error
					return;
				}

				if (mesh->Vertices() == nullptr ||
					mesh->Colors() == nullptr ||
					mesh->Triangles() == nullptr)
				{
					// todo : throw error
					return;
				}

				if (mesh->VerticesCount() != mesh->ColorsCount())
				{
					// todo : throw error
					return;
				}				

				for (unsigned int i = 0; i < mesh->TrianglesCount(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (mesh->Triangles()[i][j] > mesh->VerticesCount() - 1)
						{
							// todo : throw error
							return;
						}
					}
				}

				this->_mesh = mesh;
				this->GenerateArrays(mesh);
				this->CreateShader(mesh);
			}

			void GenerateArrays(MeshType<T> * mesh)
			{
				// generate the vertex position, color and triangle index arrays
				glGenVertexArrays(1, _vertex_array_objects);
				glBindVertexArray(_vertex_array_objects[0]);

				glGenBuffers(1, _vertex_buffer_objects);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_objects[0]);
				glBufferData(GL_ARRAY_BUFFER,
					mesh->VerticesSize() + mesh->ColorsSize(),
					NULL, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, mesh->VerticesSize(), mesh->Vertices());
				glBufferSubData(GL_ARRAY_BUFFER, mesh->VerticesSize(), mesh->ColorsSize(), mesh->Colors());

				glGenBuffers(1, _vertex_element_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertex_element_buffer[0]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					mesh->TrianglesSize(),
					mesh->Triangles(),
					GL_STATIC_DRAW);
			}

            void CreateShader(MeshType<float> * mesh)
            {                                
#ifdef __APPLE__
                ShaderInfo  shaders[] = {
                    { GL_VERTEX_SHADER, "src/shaders/GLSL/default.vert" },
                    { GL_FRAGMENT_SHADER, "src/shaders/GLSL/default.frag" },
					{ GL_GEOMETRY_SHADER, "src/shaders/GLSL/default.geom" },
                    { GL_NONE, NULL }
                };
#else
                ShaderInfo  shaders[] = {
                    { GL_VERTEX_SHADER, "src\\shaders\\GLSL\\default.vert" },
                    { GL_FRAGMENT_SHADER, "src\\shaders\\GLSL\\default.frag" },
					{ GL_GEOMETRY_SHADER, "src\\shaders\\GLSL\\default.geom" },
                    { GL_NONE, NULL }
                };
#endif
                
                _shader_program = LoadShaders(shaders);
                
                glUseProgram(_shader_program);
                
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)mesh->VerticesSize());           

                _model_matrix_uniform = glGetUniformLocation(_shader_program, "model_matrix");
                _projection_matrix_uniform = glGetUniformLocation(_shader_program, "projection_matrix");
                
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
            }
        
			void CreateShader(MeshType<double> * mesh)
            {
    #ifdef __APPLE__
                ShaderInfo  shaders[] = {
                    { GL_VERTEX_SHADER, "src/shaders/GLSL/defaultd.vert" },
                    { GL_FRAGMENT_SHADER, "src/shaders/GLSL/defaultd.frag" },
					{ GL_GEOMETRY_SHADER, "src/shaders/GLSL/defaultd.geom" },
                    { GL_NONE, NULL }
                };
    #else
                ShaderInfo  shaders[] = {
                    { GL_VERTEX_SHADER, "src\\shaders\\GLSL\\defaultd.vert" },
                    { GL_FRAGMENT_SHADER, "src\\shaders\\GLSL\\defaultd.frag" },				
					{ GL_GEOMETRY_SHADER, "src\\shaders\\GLSL\\defaultd.geom" },
                    { GL_NONE, NULL }
                };
    #endif
                _shader_program = LoadShaders(shaders);
                
                glUseProgram(_shader_program);
                
				glVertexAttribLPointer(0, 4, GL_DOUBLE, 0, NULL);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)mesh->VerticesSize());
                
                _model_matrix_uniform = glGetUniformLocation(_shader_program, "model_matrix");
                _projection_matrix_uniform = glGetUniformLocation(_shader_program, "projection_matrix");
                
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
            }

			void Draw(ObjectType<float> * parent_object)
			{
				if (this->_mesh == nullptr)
					return;

				glUseProgram(_shader_program);
				glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, Camera::MainCamera()->ProjectionMatrix());
				glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE,
					parent_object->LocalTransform()->ComposedMatrix().Multiply(Camera::MainCamera()->ViewMatrix()));

				glBindVertexArray(_vertex_array_objects[0]);
				glDrawElements(GL_TRIANGLES, this->_mesh->TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
			}

			void Draw(ObjectType<double> * parent_object)
            {
                if (this->_mesh == nullptr)
                    return;
             
                glUseProgram(_shader_program);
				glUniformMatrix4dv(_projection_matrix_uniform, 1, GL_FALSE, Camerad::MainCamera()->ProjectionMatrix());
                glUniformMatrix4dv(_model_matrix_uniform, 1, GL_FALSE,
				parent_object->LocalTransform()->ComposedMatrix().Multiply(Camerad::MainCamera()->ViewMatrix()));
				glBindVertexArray(_vertex_array_objects[0]);
				glDrawElements(GL_TRIANGLES, this->_mesh->TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
            }

			~OpenGLMeshRendererType<T>()
            {
                
            }

            OpenGLMeshRendererType<T>(RenderingContextType<T> * rendering_context)
            {
                
            }
        
		protected:
        
            RenderingContextType<T> * _rendering_context;
        
            GLuint _vertex_array_objects[1];
			GLuint _vertex_element_buffer[1];
            GLuint _vertex_buffer_objects[1];
        
            GLuint _shader_program;
            GLint _model_matrix_uniform;
            GLint _projection_matrix_uniform;
	};
    
    typedef OpenGLMeshRendererType<float> OpenGLMeshRenderer;
    typedef OpenGLMeshRendererType<double> OpenGLMeshRendererd;
}

#endif // #ifndef _opengl_mesh_renderer_h