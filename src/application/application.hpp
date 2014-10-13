//
//  Application.hpp
//  Renderer
//
//  Created by Christopher Berry on 12/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_h
#define _application_h

#ifdef EMSCRIPTEN 
#include <emscripten.h>
#endif

// systems
#include "windowing/Window.hpp"
#include "events/EventListener.hpp"
#include "rendering/OpenGL/OpenGLRenderingContext.hpp"

// content
#include "scene/Scene.hpp"
#include "rendering/Camera.hpp"
#include "geometry/MeshFactory.hpp"
#include "rendering/ShaderFactory.hpp"

// utility
#include "utility/IO.hpp"

#include <memory>

namespace Renderer
{
	class Application
	{
		public:
			explicit Application(std::shared_ptr<Window> window,
                                 std::shared_ptr<RenderingContext> rendering_context,
                                 std::shared_ptr<EventListener> event_listener);
			~Application();

			void Start();
        
        protected:
            void MainLoop();
            void End();

		private:
			std::shared_ptr<Window> _window;
			std::shared_ptr<EventListener> _event_listener;
			std::shared_ptr<RenderingContext> _rendering_context;
        
            std::unique_ptr<Scene> _scene;
	};
}

#endif // _applcation_h