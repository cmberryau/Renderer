//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//
#include "windowing\Window.h"
#include "rendering\RenderingContext.h"

using namespace Renderer;

int main(int argc, char ** argv)
{   
	Window * window = Window::Create(640, 480);
	RenderingContext * rendering_context = RenderingContext::Create(window);

	while (true)
	{
		window->HandleEvents();

		if (window->ShouldQuit())
			break;

		// Render here

		window->Swap();
	}

	return 0;
}