//
//  Application.hpp
//  Renderer
//
//  Created by Christopher Berry on 12/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_h
#define _application_h

#include "windowing/Window.hpp"
#include "rendering/RenderingContext.hpp"

namespace Renderer
{
	class Application
	{
		public:
			explicit Application(Window & window,
					 RenderingContext & rendering_context);
			~Application();
	};
}

#endif // _applcation_h