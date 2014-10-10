//
//  Window.cpp
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Window.hpp"

#include <stdio.h>
#include <stdexcept>

namespace Renderer
{
	Window::Window(int width, int height, const std::string & name) : 
	_width(width), _height(height)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{			
			throw std::runtime_error("SDL failed to initialize video");
		}

		_window_name = name;

		std::unique_ptr<SDL_Window, SDLWindowDeleter> sdl_window_ptr(SDL_CreateWindow(_window_name.c_str(),
																	 SDL_WINDOWPOS_CENTERED,
																	 SDL_WINDOWPOS_CENTERED,
																	 width, height,
																	 SDL_WINDOW_OPENGL));

		if (sdl_window_ptr.get() == nullptr)
		{
			throw std::runtime_error("SDL failed to create a window");
		}

		_sdl_window_ptr = std::move(sdl_window_ptr);
	}

	Window::~Window()
	{
		
	}

	void Window::Swap()
	{
		SDL_GL_SwapWindow(_sdl_window_ptr.get());
	}
    
    int Window::Width() const
    {
        return _width;
    }
    
    int Window::Height() const
    {
        return _height;
    }

	SDL_Window * const Window::GetSDLWindow() const
	{
		return _sdl_window_ptr.get();
	}
}