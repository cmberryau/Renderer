//
//  ApplicationFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationFactory.hpp"

namespace Renderer
{
	std::shared_ptr<Application> ApplicationFactory::FromFile(const std::string & file_path)
	{
		std::string window_name("Renderer");

		// temporary code
		std::shared_ptr<Window> window(new Window(640, 480, window_name));
#ifndef EMSCRIPTEN
		std::shared_ptr<RenderingContext> rendering_context(new OpenGLRenderingContext(*window));
#else
        std::shared_ptr<RenderingContext> rendering_context(new OpenGLESRenderingContext(*window));
#endif
		std::shared_ptr<EventListener> event_listener(new EventListener());

		std::shared_ptr<Application> app(new Application(window, rendering_context, event_listener));

		return app;
	}
}