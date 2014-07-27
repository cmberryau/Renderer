//
//  Vector.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _vector_h
#define _vector_h

//#include "Math.h"

#include <stdio.h>

namespace Renderer
{
	// 
	// Renderer::Vector<typename T, const int length>
	//
	// Generic vector implementation
	//
    template <typename T, const int len>
	class Vector
    {
		public:        
			// constructors
			Vector(){};
			Vector(T value)
			{
				for (int i = 0; i < len; i++)
				{
					elements[i] = value;
				}
			}
        
            // member functions
            inline Vector<T, len> Add(Vector<T, len> vec)
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = this[i] + vec[i];
                }
                
                return result;
            }
            
            inline Vector<T, len> Subtract(Vector<T, len> vec)
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = this[i] - vec[i];
                }
                
                return result;
            }
        
            inline Vector<T, len> Multiply(T factor)
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = this[i] * factor;
                }
                
                return result;
            }
        
            inline Vector<T, len> ComponentMultiply(Vector<T, len> vec)
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = this[i] * vec[i];
                }
                
                return result;
            }
        
            inline Vector<T, len> Divide(T factor)
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = this[i] / factor;
                }
                
                return result;
            }
        
            inline Vector<T, len> Negate()
            {
                Vector<T, len> result(0);
                
                for(int i = 0; i<len; i++)
                {
                    result[i] = -this[i];
                }
                
                return result;
            }
        
            // len(a) = sqrt(sum of elements squared)
            inline T Length()
            {
                T total = 0;
                
                for(int i = 0;i < len; i++)
                {
                    total += elements[i] * elements[i];
                }
                
                return (T)sqrt(total);
            }
        
            // normalize(a) = each element / len(a)
            inline Vector<T, len> Normalize()
            {
                Vector<T, len> result;
                T length = this->Length();
                
                for(int i = 0; i < len; i++)
                {
                    result[i] = this[i] / length;
                }
                
                return result;
            }
        
            // dist(a, b) = len(b) - len(a)
            inline T Distance(Vector<T, len> vec)
            {
                return vec.Length() - this->Length();
            }
        
            // dot(a, b) = total of elementwise multiplication
            inline T Dot(Vector<T, len> vec)
            {
                T total = 0;
                
                for(int i = 0; i < len; i++)
                {
                    total += this[i] * vec[i];
                }
                
                return total;
            }
        
            // memory size
            static inline unsigned int Size()
            {
                return sizeof(T) * len;
            }
        
			// debug output
			void Print()
			{
				for (int i = 0; i < len; i++)
				{
					printf("[%d]: %f", i, elements[i]);
				}

				printf("\n");
			}

			// operators			
			T & operator[](int n) { return elements[n]; }
			operator const T * () const { return &elements[0]; }

        protected:        
			// the actual elements of the vector
			T elements[len];
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
            Vector3(T val) : Vector<T, 3>(val){};
			Vector3(T x, T y, T z)
			{
				this->elements[0] = x;
				this->elements[1] = y;
				this->elements[2] = z;
			}

			// cross(a, b) = (a2 * b3 - a3 * b2,
			//                a3 * b1 - a1 * b3,
			//                a1 * b2 - a2 * b1)
			inline Vector<T, 3> Cross(Vector<T, 3> vec)
			{
				return Vector<T, 3>(this[1] * vec[2] - this[2] * vec[1],
									this[2] * vec[0] - this[0] * vec[2],
									this[0] * vec[1] - this[1] * vec[0]);
			}
	};

	// defined types for usage
	typedef Vector3<float> Vector3f;
  	typedef Vector3<double> Vector3d;
	typedef Vector3<unsigned int> Vector3ui;

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
	typedef Vector4<double> Vector4d;
}

#endif // _vector_h
