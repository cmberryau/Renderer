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
		std::unique_ptr<Object> camera_object(new Object());
		Camera * camera_raw = new Camera(75.0f, 1.33f, 1.0f, 500.0f);
		std::unique_ptr<ObjectAddable> camera(camera_raw);
		_scene->SetMainCamera(camera_raw);
		_scene->AddObject(camera_object);

		MainLoop();
	}
    
	void Application::AddScene(std::unique_ptr<Scene> & scene)
	{
		_scene = std::move(scene);
	}

	void Application::MainLoop()
	{
		while (true)
		{
			_event_listener->ListenForEvents();

			if (_event_listener->ShouldQuit())
			{
				return;
			}

			_rendering_context->BeginScene();

			_scene->UpdateAndDraw();

			_rendering_context->EndScene();

			_window->Swap();
		}
	}

	Scene & Application::GetScene()
	{
		return *_scene;
	}

	Window & Application::GetWindow()
	{
		return *_window;
	}

	EventListener & Application::GetEventListener()
	{
		return *_event_listener;
	}

	RenderingContext & Application::GetRenderingContext()
	{
		return *_rendering_context;
	}
}