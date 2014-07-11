#include "OpenGLMeshRenderer.h"
#include "utility/LoadShaders.h"
#include "math/Matrix.h"

namespace Renderer
{
    OpenGLMeshRenderer * OpenGLMeshRenderer::Create()
    {
        return new OpenGLMeshRenderer();
    }
    
	void OpenGLMeshRenderer::Store(Mesh * mesh)
    {
        if(mesh == nullptr)
        {
            return;
        }
        
        glGenVertexArrays(1, _vertex_array_objects);
        glBindVertexArray(_vertex_array_objects[0]);
        
        glGenBuffers(1, _vertex_buffer_objects);
        glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_objects[0]);
        glBufferData(GL_ARRAY_BUFFER,
                     mesh->VerticesSize(),
                     mesh->Vertices(),
                     GL_STATIC_DRAW);
        
#ifdef __APPLE__
        ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER, "src/shaders/GLSL/default.vert" },
            { GL_FRAGMENT_SHADER, "src/shaders/GLSL/default.frag" },
            { GL_NONE, NULL }
        };
#else
        ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER, "src\\shaders\\GLSL\\default.vert" },
            { GL_FRAGMENT_SHADER, "src\\shaders\\GLSL\\default.frag" },
            { GL_NONE, NULL }
        };
#endif
        
        _shader_program = LoadShaders(shaders);
        
        glUseProgram(_shader_program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        _model_matrix_uniform = glGetUniformLocation(_shader_program, "model_matrix");
        _projection_matrix_uniform = glGetUniformLocation(_shader_program, "projection_matrix");
        
        glEnableVertexAttribArray(0);
    }
    
    void OpenGLMeshRenderer::Draw()
    {
        Matrix4f projection_matrix = Matrix4f::Perspective(75.0f, 1.33f, 1.0f, 500.0f);
        
        glUseProgram(_shader_program);
        glUniformMatrix4fv(_projection_matrix_uniform, 1, GL_FALSE, projection_matrix);
        
        Matrix4f model_matrix = Matrix4f::Translate(0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(_model_matrix_uniform, 1, GL_FALSE, model_matrix);
        
        glBindVertexArray(_vertex_array_objects[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
 	OpenGLMeshRenderer::~OpenGLMeshRenderer()
	{
		
	}
    
	OpenGLMeshRenderer::OpenGLMeshRenderer() : _rendering_context(nullptr)
	{

	}
}