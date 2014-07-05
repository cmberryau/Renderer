#include "Window.h"

namespace Renderer
{
	Window * Window::Create(int width, int height)
	{
		Window * window = new Window();

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

	void Window::HandleEvents()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				_should_quit = true;
			}
		}
	}

	bool Window::ShouldQuit()
	{
		return _should_quit;
	}

	Window::Window() : _should_quit(false)
	{

	}

	Window::~Window()
	{

	}
}