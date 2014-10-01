//
//  Math.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Mathf.hpp"

namespace Renderer
{
	const float Mathf::Rad2Deg(float rad)
	{
		return rad * kDegsinRad;
	}

	const float Mathf::Deg2Rad(float deg)
	{
		return deg * kRadsinDeg;
	}
}