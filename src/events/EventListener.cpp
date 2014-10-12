//
//  EventListener.cpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "EventListener.hpp"

#include <stdexcept>

void EventListener::ListenForEvents()
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

bool EventListener::ShouldQuit() const
{
	return _should_quit;
}

EventListener::EventListener() : _should_quit(false)
{
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
	{
		throw std::runtime_error("SDL failed to initialize events");
	}
}

EventListener::~EventListener()
{

}