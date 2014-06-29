//
//  Math.h
//  Renderer
//
//  Created by Christopher Berry on 29/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _math_h
#define _math_h

#define M_PI_4 0.785398163397448309616

#include <math.h>

namespace Renderer
{
	template <typename T> class
	Math
	{
		public:
			// static member functions
			static T Rad2Deg(T rad)
			{
				return rad * (180.0 / M_PI);
			}
			static T Deg2Rad(T deg)
			{
				return deg / (180.0 / M_PI);
			}
	};
}

#endif  // _math_h