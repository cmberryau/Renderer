//
//  Vector.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _vector_h
#define _vector_h

namespace Renderer
{
    template <typename T, const int length> class Vector
    {
		public:
			Vector(){};

			Vector(T value)
			{
				for (int i = 0; i < length; i++)
				{
					elements[i] = value;
				}
			}

			T & operator[](int n) { return elements[n]; }
			operator const T * () const { return &elements[0]; }

        protected:
			T elements[length];
    };

	template <typename T> class Vector2 : public Vector <T, 2>
	{
		public:
			Vector2(){};
			Vector2(T x, T y);
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;
	typedef Vector2<double> Vector2d;
	
	template <typename T> class Vector3 : public Vector <T, 3>
	{
        public:
			Vector3(){};
			Vector3(T x, T y, T z);
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;
	typedef Vector3<double> Vector3d;

	template <typename T> class Vector4 : public Vector <T, 4>
	{
		public:
			Vector4(){};
			Vector4(T x, T y, T z, T w);
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<unsigned int> Vector4ui;
	typedef Vector4<double> Vector4d;
}

#endif // _vector_h

namespace Renderer
{
	template <typename T> Vector2<T>::Vector2(T x, T y)
	{
		this->elements[0] = x;
		this->elements[1] = y;
	}

	template <typename T> Vector3<T>::Vector3(T x, T y, T z)
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->elements[2] = z;
	}

	template <typename T> Vector4<T>::Vector4(T x, T y, T z, T w)
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->elements[2] = z;
		this->elements[3] = w;
	}
}
