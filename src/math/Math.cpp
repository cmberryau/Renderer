//
//  Math.cpp
//  Renderer
//
//  Created by Christopher Berry on 29/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Math.h"

namespace Renderer
{
	template <typename T>
	static T Math<T>::Rad2Deg(T rad)
	{
		return rad * (180.0 / M_PI);
	}

	template <typename T>
	static T Math<T>::Deg2Rad(T deg)
	{
		return deg / (180.0 / M_PI);
	}
}