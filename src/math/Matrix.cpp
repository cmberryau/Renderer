//
//  Matrix.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Matrix.h"

namespace Renderer
{
	template <typename T> Matrix4<T>::Matrix4(T e00, T e01, T e02, T e03,
											  T e10, T e11, T e12, T e13,
											  T e20, T e21, T e22, T e23,
											  T e30, T e31, T e32, T e33)
	{
		elements[0].x = e00; elements[0].y = e10; elements[0].z = e20; elements[0].w = e30;
		elements[1].x = e01; elements[1].y = e11; elements[1].z = e21; elements[1].w = e31;
		elements[2].x = e02; elements[2].y = e12; elements[2].z = e22; elements[2].w = e32;
		elements[3].x = e03; elements[3].y = e13; elements[3].z = e23; elements[3].w = e33;
	}
}