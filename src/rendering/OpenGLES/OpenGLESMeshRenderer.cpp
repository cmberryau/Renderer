//
//  OpenGLESMeshRenderer.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "OpenGLESMeshRenderer.hpp"
#include "scene/Scene.hpp"

namespace Renderer
{
    OpenGLESMeshRenderer::OpenGLESMeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr)
    : MeshRenderer(rendering_context_ptr)
    {
        
    }

	OpenGLESMeshRenderer::~OpenGLESMeshRenderer()
	{
        /*
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
        */
	}

    void OpenGLESMeshRenderer::AddMesh(const std::shared_ptr<Mesh> & mesh_ptr)
    {
        if(HasMesh())
        {
            throw std::runtime_error("Multiple meshes on a single MeshRenderer are not supported yet");
        }
        
        // attempt to validate the mesh first
        try {
            mesh_ptr->Validate();
        } catch (std::exception e) {
            throw std::runtime_error("Mesh failed to validate");
        }
        
        SetMesh(mesh_ptr);
        
        // upload resources to opengl and prepare shader
        GenerateArrays(GetMesh());
        CreateShader(GetMesh());
    }

	void OpenGLESMeshRenderer::GenerateArrays(const Mesh & mesh)
	{
		glGenBuffers(1, &_vertex_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.VerticesSize(), mesh.Vertices(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_vertex_normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.VertexNormalsSize(), mesh.VertexNormals(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_vertex_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.ColorsSize(), mesh.Colors(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_triangle_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.TrianglesSize(), mesh.Triangles(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLESMeshRenderer::CreateShader(const Mesh & mesh)
	{
        GetMaterial().Use();

		const OpenGLESShader * opengles_shader = static_cast<const OpenGLESShader *>(GetMaterial().GetShader());

		_model_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "model_matrix");
		_normal_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "normal_matrix");
		_projection_matrix_uniform = glGetUniformLocation(opengles_shader->Program(), "projection_matrix");
	}

	void OpenGLESMeshRenderer::Draw(Object & parent_object, const Scene & scene) const
	{
        if(!HasMesh())
        {
            return;
        }
        
        GetMaterial().Use();

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

        glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, scene.MainCamera().ProjectionMatrix());
        glUniformMatrix4fv(_normal_matrix_uniform, 1, GL_FALSE, parent_object.LocalTransform().NormalMatrix().Multiply(scene.MainCamera().ViewMatrix()));
        glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, parent_object.LocalTransform().ComposedMatrix().Multiply(scene.MainCamera().ViewMatrix()));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _triangle_index_buffer);
		glDrawElements(GL_TRIANGLES, GetMesh().TrianglesCount() * 3, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

#endif // EMSCRIPTEN