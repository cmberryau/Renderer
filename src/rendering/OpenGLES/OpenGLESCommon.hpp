//
//  OpenGLESCommon.hpp
//  Renderer
//
//  Created by Christopher Berry on 13/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifdef EMSCRIPTEN

#ifndef _opengl_common_h
#define _opengl_common_h

#include <SDL2/SDL_opengles2.h>

namespace Renderer
{
	void CheckForGLESError();
}

#endif

#endif