//
//  Application.cpp
//  Renderer
//
//  Created by Christopher Berry on 12/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Application.hpp"

namespace Renderer
{
	Application::Application(std::shared_ptr<Window> window,
		std::shared_ptr<RenderingContext> rendering_context,
		std::shared_ptr<EventListener> event_listener) :
		_window(window),
		_event_listener(event_listener),
		_rendering_context(rendering_context)		
	{

	}

	Application::~Application()
	{
		SDL_Quit();
	}

	void Application::Run()
	{
		while (true)
		{
			_event_listener->ListenForEvents();

			if (_event_listener->ShouldQuit())
			{
				return;
			}			

			_rendering_context->BeginScene();

			_rendering_context->EndScene();

			_window->Swap();
		}
	}
}