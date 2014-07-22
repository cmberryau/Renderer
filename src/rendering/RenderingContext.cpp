#include "RenderingContext.h"
#include "rendering/OpenGL/OpenGLRenderingContext.h"

namespace Renderer
{
	RenderingContextType RenderingContext::Type()
	{
		return _context_type;
	}
    
	RenderingContext::~RenderingContext()
	{
        
	}

	RenderingContext::RenderingContext(RenderingContextType context_type,
									   RenderingContextPrecision context_precision)
	: _context_type(context_type), _precision(context_precision)
	{

	}
}