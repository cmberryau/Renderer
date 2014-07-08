//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//
#include "windowing/Window.h"
#include "events/EventListener.h"
#include "rendering/RenderingContext.h"

using namespace Renderer;

int main(int argc, char ** argv)
{   
	Window * window = Window::Create(640, 480);
	EventListener * event_listener = EventListener::Create();
	RenderingContext * rendering_context = RenderingContext::Create(window, OpenGLContextType);

	while (true)
	{
		event_listener->ListenForEvents();

		if (event_listener->ShouldQuit())
			break;
        
		// work on figuring out rendering pattern

		// Render here

		window->Swap();
	}

	return 0;
}