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
	const float Mathf::kDegsinRad = 57.2957795130823208768f;
	const float Mathf::kRadsinDeg = 0.01745329251994329576f;

	float Mathf::Rad2Deg(float rad)
	{
		return rad * kDegsinRad;
	}

	float Mathf::Deg2Rad(float deg)
	{
		return deg * kRadsinDeg;
	}
}