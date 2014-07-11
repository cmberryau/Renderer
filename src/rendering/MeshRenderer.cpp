#include "MeshRenderer.h"
#include "OpenGLMeshRenderer.h"

namespace Renderer
{
    MeshRenderer * MeshRenderer::Create(RenderingContext * rendering_context)
    {
		MeshRenderer * mesh_renderer = nullptr;

        if(rendering_context->Type() == OpenGLContextType)
        {
			mesh_renderer = new OpenGLMeshRenderer();
        }
        
		return mesh_renderer;
    }
    
 	MeshRenderer::~MeshRenderer()
	{
		
	}
    
	MeshRenderer::MeshRenderer() : _rendering_context(nullptr)
	{

	}
}