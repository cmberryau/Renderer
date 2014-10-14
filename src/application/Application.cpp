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

	void Application::Start()
	{
        std::unique_ptr<Scene> scene(new Scene());
        _scene = std::move(scene);
        
        
        
		while (true)
		{
			MainLoop();
		}
	}
    
	void Application::MainLoop()
	{
		_event_listener->ListenForEvents();

		if (_event_listener->ShouldQuit())
		{
			End();
		}

		_rendering_context->BeginScene();

		_scene->UpdateAndDraw();

		_rendering_context->EndScene();

		_window->Swap();
	}

    void Application::End()
    {
        _scene.reset();        
        exit(0);
    }

	EventListener & Application::GetEventListener()
	{
		return *_event_listener;
	}

	RenderingContext & Application::GetRenderingContext()
	{
		return *_rendering_context;
	}

	Window & Application::GetWindow()
	{
		return *_window;
	}
}