#include "MeshRenderer.h"
#include "rendering/OpenGL/OpenGLMeshRenderer.h"

namespace Renderer
{
    MeshRenderer * MeshRenderer::Create(RenderingContext * rendering_context)
    {
		MeshRenderer * mesh_renderer = nullptr;

        if(rendering_context->Type() == OpenGLContextType)
        {
			mesh_renderer = OpenGLMeshRenderer::Create(rendering_context);
        }
        
		return mesh_renderer;
    }
    
 	MeshRenderer::~MeshRenderer()
	{
		
	}
    
	MeshRenderer::MeshRenderer() : _rendering_context(nullptr),
								   _mesh(nullptr)
	{

	}
}