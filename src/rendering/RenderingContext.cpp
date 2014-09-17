//
//  RenderingContext.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "RenderingContext.hpp"

namespace Renderer
{
	void RenderingContext::SetCamera(Camera * camera)
	{
		if (camera == nullptr)
		{
			return;
		}

		this->_camera = camera;
	}

	Camera * RenderingContext::MainCamera()
	{
		return _camera;
	}

	Window * RenderingContext::Window()
	{
		return _window;
	}
}
