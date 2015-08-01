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

		EmscriptenApplication::Instance().GetRenderingContext().BeginScene();

        EmscriptenApplication::Instance().GetScene().UpdateAndDraw();
        
		EmscriptenApplication::Instance().GetRenderingContext().EndScene();

		EmscriptenApplication::Instance().GetWindow().Swap();
	}

	EmscriptenApplication * EmscriptenApplication::_instance = nullptr;

	EmscriptenApplication::EmscriptenApplication(std::shared_ptr<Window> window,
												 std::shared_ptr<RenderingContext> rendering_context,
												 std::shared_ptr<EventListener> event_listener) :
												 Application(window, rendering_context, event_listener)
	{
        EmscriptenApplication::_instance = this;
	}

	void EmscriptenApplication::Start()
	{        
        std::unique_ptr<Object> camera_object(new Object());
        Camera * camera_raw = new Camera(75.0f, 1.33f, 1.0f, 500.0f);
        std::unique_ptr<ObjectAddable> camera(camera_raw);
        GetScene().SetMainCamera(camera_raw);
        GetScene().AddObject(camera_object);
        
		emscripten_set_main_loop(EmscriptenLoop, 0, true);
	}

	EmscriptenApplication & EmscriptenApplication::Instance()
	{        
		return *_instance;
	}
}

#endif