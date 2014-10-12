//
//  OpenGLESMeshRenderer.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "OpenGLESMeshRenderer.hpp"

namespace Renderer
{
	OpenGLESMeshRenderer::OpenGLESMeshRenderer(RenderingContext * rendering_context)
	: MeshRenderer(rendering_context)
	{

	}

	OpenGLESMeshRenderer::~OpenGLESMeshRenderer()
	{
		if (glIsBuffer(&_vertex_position_buffer))
		{
			glDeleteBuffers(1, _vertex_position_buffer);
		}

		if (glIsBuffer(&_vertex_normal_buffer))
		{
			glDeleteBuffers(1, _vertex_normal_buffer);
		}

		if (glIsBuffer(&_vertex_color_buffer))
		{
			glDeleteBuffers(1, _vertex_color_buffer);
		}

		if (glIsBuffer(&_triangle_index_buffer))
		{
			glDeleteBuffers(1, _triangle_index_buffer);
		}
	}

	void OpenGLESMeshRenderer::SetMesh(Mesh * mesh)
	{
		if (mesh == nullptr)
		{
			throw std::exception();
		}

		mesh->Validate();
		this->_mesh = mesh;

		this->GenerateBuffers(mesh);
		this->SetupShader(mesh);
	}

	void OpenGLESMeshRenderer::GenerateBuffers(Mesh * mesh)
	{
		glGenBuffers(1, &_vertex_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->VerticesSize(), mesh->Vertices(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_vertex_normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->VertexNormalsSize(), mesh->VertexNormals(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_vertex_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->ColorsSize(), mesh->Colors(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_triangle_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->TrianglesSize(), mesh->Triangles(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLESMeshRenderer::SetupShader(Mesh * mesh)
	{
		this->_material->Use();

		OpenGLESShader * opengles_shader = dynamic_cast<OpenGLESShader *>(this->_material->Shader());

		_model_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "model_matrix");
		_normal_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "normal_matrix");
		_projection_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "projection_matrix");
	}

	void OpenGLESMeshRenderer::Draw(Object * parent_object)
	{
		if (this->_mesh == nullptr)
		{
			throw std::exception();
		}

		this->_material->Use();

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_position_buffer);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_normal_buffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_color_buffer);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, this->_rendering_context->MainCamera()->ProjectionMatrix());
		glUniformMatrix4fv(_normal_matrix_uniform, 1, GL_FALSE, parent_object->LocalTransform()->NormalMatrix().Multiply(this->_rendering_context->MainCamera()->ViewMatrix()));
		glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, parent_object->LocalTransform()->ComposedMatrix().Multiply(this->_rendering_context->MainCamera()->ViewMatrix()));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
		glDrawElements(GL_TRIANGLES, this->_mesh->TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

#endif // EMSCRIPTEN