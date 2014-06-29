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

namespace Renderer
{
	template <typename T> class
	Math
	{
		public:
	
		static T Rad2Deg(T rad);
		static T Deg2Rad(T deg);
	};
}

#endif  // _math_h