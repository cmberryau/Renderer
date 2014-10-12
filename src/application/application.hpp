//
//  Application.hpp
//  Renderer
//
//  Created by Christopher Berry on 12/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_h
#define _application_h

#ifdef EMSCRIPTEN
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "windowing/Window.hpp"
#include "events/EventListener.hpp"
#include "rendering/OpenGL/OpenGLRenderingContext.hpp"

#include <memory>

namespace Renderer
{
	class Application
	{
		public:
			explicit Application(std::shared_ptr<Window> window,
			std::shared_ptr<RenderingContext> rendering_context,
			std::shared_ptr<EventListener> event_listener);
			~Application();

			void Run();

		private:
			std::shared_ptr<Window> _window;
			std::shared_ptr<EventListener> _event_listener;
			std::shared_ptr<RenderingContext> _rendering_context;			
	};
}

#endif // _applcation_h