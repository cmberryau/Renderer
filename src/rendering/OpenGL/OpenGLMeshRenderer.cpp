//
//  OpenGLMeshRenderer.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLMeshRenderer.hpp"

namespace Renderer
{
	OpenGLMeshRenderer::OpenGLMeshRenderer(RenderingContext * rendering_context) 
	: MeshRenderer(rendering_context)
	{

	}

	OpenGLMeshRenderer::~OpenGLMeshRenderer()
	{

	}

	bool OpenGLMeshRenderer::CheckForGLError()
	{
		GLenum error;
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			fprintf(stderr, "OpenGL error: %d\n", error);
			return true;
		}

		return false;
	}

	void OpenGLMeshRenderer::SetMesh(Mesh * mesh)
	{
		if (mesh == nullptr)
		{
			throw std::exception();
		}

		mesh->Validate();

		this->GenerateArrays(mesh);
		this->CreateShader(mesh);
		this->_mesh = mesh;
	}

	void OpenGLMeshRenderer::GenerateArrays(Mesh * mesh)
	{
		// generate the vertex position, color and triangle index arrays
		glGenVertexArrays(1, _vertex_array_objects);
		glBindVertexArray(_vertex_array_objects[0]);

		glGenBuffers(1, _vertex_buffer_objects);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_objects[0]);
		glBufferData(GL_ARRAY_BUFFER, mesh->VerticesSize() + mesh->VertexNormalsSize() + mesh->ColorsSize(), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, mesh->VerticesSize(), mesh->Vertices());
		glBufferSubData(GL_ARRAY_BUFFER, mesh->VerticesSize(), mesh->VertexNormalsSize(), mesh->VertexNormals());
		glBufferSubData(GL_ARRAY_BUFFER, mesh->VerticesSize() + mesh->VertexNormalsSize(), mesh->ColorsSize(), mesh->Colors());

		glGenBuffers(1, _vertex_element_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertex_element_buffer[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->TrianglesSize(), mesh->Triangles(), GL_STATIC_DRAW);
	}

	void OpenGLMeshRenderer::CreateShader(Mesh * mesh)
	{
		this->_material->Use();

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid *>(mesh->VerticesSize()));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid *>(mesh->VerticesSize() + mesh->VertexNormalsSize()));

		OpenGLShader * opengl_shader = dynamic_cast<OpenGLShader *>(this->_material->Shader());

		_model_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "model_matrix");
		_normal_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "normal_matrix");
		_projection_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "projection_matrix");

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	void OpenGLMeshRenderer::Draw(Object * parent_object)
	{
		if (this->_mesh == nullptr)
			return;

		this->_material->Use();

		glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, this->_rendering_context->MainCamera()->ProjectionMatrix());
		glUniformMatrix4fv(_normal_matrix_uniform, 1, GL_FALSE, parent_object->LocalTransform()->NormalMatrix().Multiply(this->_rendering_context->MainCamera()->ViewMatrix()));
		glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, parent_object->LocalTransform()->ComposedMatrix().Multiply(this->_rendering_context->MainCamera()->ViewMatrix()));

		glBindVertexArray(_vertex_array_objects[0]);
		glDrawElements(GL_TRIANGLES, this->_mesh->TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
	}
}