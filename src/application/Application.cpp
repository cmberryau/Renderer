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
		Scene scene;		
		Camera main_camera(75.0f, 1.33f, 1.0f, 500.0f);

		while (true)
		{
			_event_listener->ListenForEvents();

			if (_event_listener->ShouldQuit())
			{
				return;
			}			

			_rendering_context->BeginScene();

			scene.UpdateAndDraw();

			_rendering_context->EndScene();

			_window->Swap();
		}
	}
}