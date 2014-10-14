//
//  EmscriptenApplication.hpp
//  Renderer
//
//  Created by Christopher Berry on 13/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN 

#ifndef _emscripten_application_h
#define _emscripten_application_h

#include "application/Application.hpp"

#include <emscripten.h>

namespace Renderer
{
	class EmscriptenApplication : public Application
	{
		friend void EmscriptenLoop();

		public:
			explicit EmscriptenApplication(std::shared_ptr<Window> window,
										   std::shared_ptr<RenderingContext> rendering_context,
										   std::shared_ptr<EventListener> event_listener);
			virtual ~EmscriptenApplication(){};

			virtual void Start() override;

		protected:
			static EmscriptenApplication & Instance();

		private:
			static EmscriptenApplication * _instance;
	};
}

#endif

#endif