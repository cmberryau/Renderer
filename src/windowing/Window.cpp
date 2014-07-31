//
//  Window.cpp
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Window.hpp"

#include <stdio.h>

namespace Renderer
{
	Window * Window::Create(int width, int height)
	{
		Window * window = new Window(width, height);

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			fprintf(stdout, "SDL_Init failed!\n");
			return nullptr;
		}

		window->_sdl_window = SDL_CreateWindow("Renderer",
											   SDL_WINDOWPOS_CENTERED,
											   SDL_WINDOWPOS_CENTERED,
											   width, height,
											   SDL_WINDOW_OPENGL);

		return window;
	}

	void Window::Swap()
	{
		SDL_GL_SwapWindow(_sdl_window);
	}
    
    int Window::Width()
    {
        return _width;
    }
    
    int Window::Height()
    {
        return _height;
    }

	Window::~Window()
	{
        SDL_DestroyWindow(_sdl_window);
		SDL_Quit();
	}

	Window::Window(int width, int height)
    : _width(width), _height(height)
	{

	}
}