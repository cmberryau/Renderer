//
//  OpenGLCommon.hpp
//  Renderer
//
//  Created by Christopher Berry on 6/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef EMSCRIPTEN

#ifndef _opengl_common_h
#define _opengl_common_h

// OpenGL includes
#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <SDL2/SDL_opengl.h>

namespace Renderer
{
	void CheckForGLError();
}

#endif

#endif