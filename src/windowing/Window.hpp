//
//  Window.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _window_h
#define _window_h

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL2/SDL.h>

#include <string>
#include <memory>

namespace Renderer
{
	class Window
	{
		public:
			explicit Window(int width, int height, const std::string & name);
			~Window();

			void Swap();
            int Width() const;
            int Height() const;
			SDL_Window * const GetSDLWindow() const;

		private:
			struct SDLWindowDeleter
			{
				void operator()(SDL_Window * window)
				{
					SDL_DestroyWindow(window);
				}
			};

			int _width, _height;
			std::string _window_name;
			std::unique_ptr<SDL_Window, SDLWindowDeleter> _sdl_window_ptr;
	};
}

#endif // _window_h