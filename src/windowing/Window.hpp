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

namespace Renderer
{
	class Window
	{
		public:
			static Window * Create(int width, int height);
			void Swap();

			~Window();

			SDL_Window * _sdl_window;

		protected:
			Window();
	};
}

#endif // #ifndef _window_h