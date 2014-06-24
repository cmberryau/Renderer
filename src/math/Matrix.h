//
//  Matrix.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _matrix_h
#define _matrix_h

#include "Vector.h"

namespace Renderer
{
	template<typename T, const int w, const int h> class Matrix
	{
		public:
			Matrix(){};

		protected:
			Vector<T, h> elements[w];
	};

	template<typename T> class Matrix4 : Matrix < T, 4, 4 >
	{
		public:
			Matrix4(){};
			Matrix4(T e00, T e01, T e02, T e03,
					T e10, T e11, T e12, T e13,
					T e20, T e21, T e22, T e23,
					T e30, T e31, T e32, T e33);
	};
}

#endif // _matrix_h