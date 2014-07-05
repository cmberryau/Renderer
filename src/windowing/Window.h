//
//  Window.h
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

#include <SDL2\SDL.h>

#include <stdio.h>

namespace Renderer
{
	class Window
	{
		public:
			static Window * Create(int width, int height);
			void Swap();
			void HandleEvents();
			bool ShouldQuit();

			~Window();

			SDL_Window * _sdl_window;

		protected:
			Window();
			bool _should_quit;
	};
}

#endif // #ifndef _window_h