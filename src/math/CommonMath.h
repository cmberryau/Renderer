//
//  CommonMath.h
//  Renderer
//
//  Created by Christopher Berry on 29/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _math_h
#define _math_h

#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

namespace Renderer
{
    template <typename T>
	class Math
	{
		public:
			// static member functions
			static T Rad2Deg(T rad)
			{
				return rad * (180.0 / (T)M_PI);
			}

			static T Deg2Rad(T deg)
			{
				return deg / (180.0 / (T)M_PI);
			}
	};
    
    typedef Math<float> Mathf;
}

#endif  // _math_h