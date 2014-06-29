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
	// 
	// Renderer::Vector<typename T, const int length>
	//
	// Generic vector implementation
	//
    template <typename T, const int length> 
	class Vector
    {
		public:        
			// constructors
			Vector(){};
			Vector(T value)
			{
				for (int i = 0; i < length; i++)
				{
					elements[i] = value;
				}
			}

			// operators
			// [] operator allows array subscript style access
			T & operator[](int n) { return elements[n]; }
			// allows casting to an array
			operator const T * () const { return &elements[0]; }

        protected:        
			// the actual elements of the vector
			T elements[length];
    };

	// 
	// Renderer::Vector2<typename T>
	//
	// Generic 2 element vector implementation
	//
	template <typename T> 
	class Vector2 : public Vector <T, 2>
	{
		public:
			// constructors
			Vector2(){};
			Vector2(T x, T y)
			{
				this->elements[0] = x;
				this->elements[1] = y;
			}
	};

	// defined types for usage
	typedef Vector2<float> Vector2f;
	
	// 
	// Renderer::Vector3<typename T>
	//
	// Generic 3 element vector implementation
	//
	template <typename T> class 
	Vector3 : public Vector <T, 3>
	{
        public:
			// constructors
			Vector3(){};
			Vector3(T x, T y, T z)
			{
				this->elements[0] = x;
				this->elements[1] = y;
				this->elemernts[2] = z;
			}
	};

	// defined types for usage
	typedef Vector3<float> Vector3f;

	// 
	// Renderer::Vector4<typename T>
	//
	// Generic 4 element vector implementation
	//
	template <typename T> class 
	Vector4 : public Vector <T, 4>
	{
		public:
			// constructors
			Vector4(){};
			Vector4(T x, T y, T z, T w)
			{
				this->elements[0] = x;
				this->elements[1] = y;
				this->elements[2] = z;
				this->elements[3] = w;
			}
	};

	// defined types for usage
	typedef Vector4<float> Vector4f;
}

#endif // _vector_h
