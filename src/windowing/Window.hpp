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

#ifdef EMSCRIPTEN
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace Renderer
{
	class Window
	{
		public:        
			void Swap();
        
            int Width();
            int Height();
			
			Window(int width, int height);
			~Window();

			SDL_Window * _sdl_window;

		protected:		        
            int _width, _height;
	};
}

#endif // _window_h