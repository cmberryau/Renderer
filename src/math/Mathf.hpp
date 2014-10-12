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
			static float Rad2Deg(float rad);
			static float Deg2Rad(float deg);
        
        protected:
            static const float kDegsinRad;
            static const float kRadsinDeg;
	};
}

#endif  // _math_h