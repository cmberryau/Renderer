#include "MeshRenderer.h"

namespace Renderer
{
    MeshRenderer * MeshRenderer::Create(RenderingContext * rendering_context)
    {
        if(rendering_context->Type() == OpenGLContextType)
        {
            
        }
        
        return nullptr;
    }
    
 	MeshRenderer::~MeshRenderer()
	{
		
	}
    
	MeshRenderer::MeshRenderer() : _rendering_context(nullptr)
	{

	}
}