#include "RenderingContext.h"
#include "rendering/OpenGL/OpenGLRenderingContext.h"

namespace Renderer
{
	RenderingContext * RenderingContext::Create(Window * window, RenderingContextType context_type)
	{
		if (window == nullptr)
			return nullptr;
        
        RenderingContext * context = nullptr;
        
        if(context_type == OpenGLContextType)
        {
            context = OpenGLRenderingContext::Create(window, 4, 4);
            context->_window = window;
        }

		return context;
	}

	RenderingContextType RenderingContext::Type()
	{
		return _context_type;
	}
    
	RenderingContext::~RenderingContext()
	{
        
	}
    
	RenderingContext::RenderingContext()
	{

	}
}