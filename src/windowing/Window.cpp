//
//  Window.cpp
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Window.hpp"

#include <stdio.h>
#include <exception>

namespace Renderer
{
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

	Window::Window(int width, int height)
    : _width(width), _height(height)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw std::exception("SDL_Init failed!\n");
		}

		_sdl_window = SDL_CreateWindow("Renderer",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   width, height,
									   SDL_WINDOW_OPENGL);

		if (_sdl_window == nullptr)
		{
			throw std::exception("SDL_CreateWindow failed!\n");
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(_sdl_window);
		SDL_Quit();
	}
}