//
//  EventListener.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _event_listener_h
#define _event_listener_h

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL2/SDL.h>

class EventListener
{
	public:
		static EventListener * Create();
		void ListenForEvents();
		bool ShouldQuit();

		~EventListener();
    
	protected:
		EventListener();

		bool _should_quit;
};

#endif // #ifndef _event_listener_h