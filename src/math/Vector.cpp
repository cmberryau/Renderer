//
//  Vector.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Vector.h"

namespace Renderer
{
	template <typename T> Vector2<T>::Vector2(T x, T y)
	{
		base::elements[0] = x;
		base::elements[1] = y;
	}

	template <typename T> Vector3<T>::Vector3(T x, T y, T z)
	{
		base::elements[0] = x;
		base::elements[1] = y;
		base::elements[2] = z;
	}

	template <typename T> Vector4<T>::Vector4(T x, T y, T z, T w)
	{
		base::elements[0] = x;
		base::elements[1] = y;
		base::elements[2] = z;
		base::elements[3] = w;
	}
}