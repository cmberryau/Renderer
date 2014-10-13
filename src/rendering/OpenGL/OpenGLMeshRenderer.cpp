//
//  OpenGLMeshRenderer.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLMeshRenderer.hpp"
#include "scene/Scene.hpp"

namespace Renderer
{   
    OpenGLMeshRenderer::OpenGLMeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr)
    : MeshRenderer(rendering_context_ptr)
    {
        
    }

	OpenGLMeshRenderer::~OpenGLMeshRenderer()
	{
		if (glIsVertexArray(_vertex_array_objects))
		{
			glDeleteVertexArrays(1, &_vertex_array_objects);
		}

		if (glIsBuffer(_vertex_buffer_objects))
		{
			glDeleteBuffers(1, &_vertex_buffer_objects);
		}

		if (glIsBuffer(_vertex_element_buffer))
		{
			glDeleteBuffers(1, &_vertex_element_buffer);
		}
	}
    
    void OpenGLMeshRenderer::AddMesh(const std::shared_ptr<Mesh> & mesh_ptr)
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

    void OpenGLMeshRenderer::GenerateArrays(const Mesh & mesh)
    {
        // generate the vertex position, color and triangle index arrays
        glGenVertexArrays(1, &_vertex_array_objects);
        glBindVertexArray(_vertex_array_objects);
        
        glGenBuffers(1, &_vertex_buffer_objects);
        glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_objects);
        glBufferData(GL_ARRAY_BUFFER, mesh.VerticesSize() + mesh.VertexNormalsSize() + mesh.ColorsSize(), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mesh.VerticesSize(), mesh.Vertices());
        glBufferSubData(GL_ARRAY_BUFFER, mesh.VerticesSize(), mesh.VertexNormalsSize(), mesh.VertexNormals());
        glBufferSubData(GL_ARRAY_BUFFER, mesh.VerticesSize() + mesh.VertexNormalsSize(), mesh.ColorsSize(), mesh.Colors());
        
        glGenBuffers(1, &_vertex_element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertex_element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.TrianglesSize(), mesh.Triangles(), GL_STATIC_DRAW);
    }
    
    void OpenGLMeshRenderer::CreateShader(const Mesh & mesh)
    {
        GetMaterial().Use();
        
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid *>(GetMesh().VerticesSize()));
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid *>(GetMesh().VerticesSize() + GetMesh().VertexNormalsSize()));

		const OpenGLShader * opengl_shader = static_cast<const OpenGLShader *>(GetMaterial().GetShader());
        
        _model_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "model_matrix");
        _normal_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "normal_matrix");
        _projection_matrix_uniform = glGetUniformLocation(opengl_shader->Program(), "projection_matrix");
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }

    void OpenGLMeshRenderer::Draw(Object & parent_object, const Scene & scene) const
    {
		if(!HasMesh())
        {
            return;
        }

		GetMaterial().Use();
        
        glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, scene.MainCamera()->ProjectionMatrix());
        glUniformMatrix4fv(_normal_matrix_uniform, 1, GL_FALSE, parent_object.LocalTransform().NormalMatrix().Multiply(scene.MainCamera()->ViewMatrix()));
		glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, parent_object.LocalTransform().ComposedMatrix().Multiply(scene.MainCamera()->ViewMatrix()));
        
        glBindVertexArray(_vertex_array_objects);
        glDrawElements(GL_TRIANGLES, static_cast<GLint>(GetMesh().TrianglesCount() * 3), GL_UNSIGNED_INT, NULL);
    }
}