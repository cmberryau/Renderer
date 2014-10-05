//
//  ApplicationFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationFactory.hpp"

namespace Renderer
{
	Application ApplicationFactory::FromFile(const std::string & file_path)
	{
		// temporary code
		Window * window = nullptr;
		RenderingContext * rendering_context = nullptr;

		Application app(*window, *rendering_context);

		return app;
	}
}