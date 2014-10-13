//
//  EmscriptenApplication.cpp
//  Renderer
//
//  Created by Christopher Berry on 13/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#include "application/EmscriptenApplication.hpp"

namespace Renderer
{
	void EmscriptenLoop()
	{
		EmscriptenApplication::Instance().GetEventListener().ListenForEvents();

		if(EmscriptenApplication::Instance().GetEventListener().ShouldQuit())
		{
			EmscriptenApplication::Instance().End();
		}

		EmscriptenApplication::Instance().GetRenderingContext().BeginScene();

		EmscriptenApplication::Instance().GetRenderingContext().EndScene();

		EmscriptenApplication::Instance().GetWindow().Swap();
	}

	std::unique_ptr<EmscriptenApplication> EmscriptenApplication::_instance = nullptr;

	EmscriptenApplication::EmscriptenApplication(std::shared_ptr<Window> window,
												 std::shared_ptr<RenderingContext> rendering_context,
												 std::shared_ptr<EventListener> event_listener) :
												 Application(window, rendering_context, event_listener)
	{
		EmscriptenApplication::_instance = std::unique_ptr<EmscriptenApplication>(this);
	}

	void EmscriptenApplication::Start()
	{
		emscripten_set_main_loop(EmscriptenLoop, 0, true);
	}

	EmscriptenApplication & EmscriptenApplication::Instance()
	{
		return *_instance;
	}
}

#endif