#include "RenderingContext.h"
#include "OpenGLRenderingContext.h"

namespace Renderer
{
	RenderingContext * RenderingContext::Create(Window * window, RenderingContextType context_type)
	{
		if (window == nullptr)
			return nullptr;
        
        RenderingContext * context = nullptr;
        
        if(context_type == OpenGLContextType)
        {
            context = OpenGLRenderingContext::Create(window);
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
		delete _window;
		SDL_Quit();
	}
    
	RenderingContext::RenderingContext()
	{

	}
}