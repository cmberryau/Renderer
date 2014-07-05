#include "EventListener.h"

EventListener * EventListener::Create()
{
	EventListener * event_listener = new EventListener();

	return event_listener;
}

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

bool EventListener::ShouldQuit()
{
	return _should_quit;
}

EventListener::~EventListener()
{

}

EventListener::EventListener() : _should_quit(false)
{

}