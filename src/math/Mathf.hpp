//
//  Math.hpp
//  Renderer
//
//  Created by Christopher Berry on 29/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _math_h
#define _math_h

#include <math.h>

namespace Renderer
{
	class Mathf
	{
		public:
			// static member functions
			static const float Rad2Deg(float rad);
			static const float Deg2Rad(float deg);
        
        protected:
            constexpr static const float kDegsinRad = 57.2957795130823208768f;
            constexpr static const float kRadsinDeg = 0.01745329251994329576f;
	};
}

#endif  // _math_h