//
//  OpenGLCommon.cpp
//  Renderer
//
//  Created by Christopher Berry on 6/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "OpenGLCommon.hpp"
#include <stdexcept>
#include <string>

namespace Renderer
{
	void CheckForGLError()
	{
		GLenum error_code = glGetError();
		if (error_code != GL_NO_ERROR)
		{
			std::string error_message("OpenGL error: ");
			throw std::runtime_error(error_message.append(std::to_string(error_code)));
		}
	}
}