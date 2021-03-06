//
//  Vector.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _vector_h
#define _vector_h

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
			Vector() = default;
			inline explicit Vector(T value)
			{
				for (int i = 0; i < len; i++)
				{
					elements[i] = value;
				}
			}

			// copy constructor
			inline Vector(const Vector & rhs)
			{
				assign(rhs);
			}
        
            // assignment operator
            inline Vector & operator = (const Vector & rhs)
            {
                assign(rhs);
                return *this;
            }
		
			// member functions
			inline Vector Add(Vector<T, len> vec)
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = elements[i] + vec[i];
				}
				
				return result;
			}
			
			inline Vector Subtract(Vector<T, len> vec)
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = elements[i] - vec[i];
				}
				
				return result;
			}
		
			inline Vector Multiply(T factor)
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = elements[i] * factor;
				}
				
				return result;
			}
		
			inline Vector ComponentMultiply(Vector<T, len> vec)
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = elements[i] * vec[i];
				}
				
				return result;
			}
		
			inline Vector Divide(T factor)
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = elements[i] / factor;
				}
				
				return result;
			}
		
			inline Vector Negate()
			{
				Vector<T, len> result(0);
				
				for(int i = 0; i<len; i++)
				{
					result[i] = -elements[i];
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
			inline Vector Normalize()
			{
				Vector<T, len> result;
				T length = this->Length();
				
				for(int i = 0; i < len; i++)
				{
					result[i] = elements[i] / length;
				}
				
				return result;
			}
		
			// dist(a, b) = len(b) - len(a)
			inline T Distance(Vector vec)
			{
				return vec.Length() - this->Length();
			}
		
			// dot(a, b) = total of elementwise multiplication
			inline T Dot(Vector vec)
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
			void Print() const
			{
				for (int i = 0; i < len; i++)
				{
					printf("[%d]: %f", i, elements[i]);
				}

				printf("\n");
			}

			inline T & operator [] (int n) 
			{ 
				return elements[n]; 
			}

			inline operator const T * () const 
			{ 
				return &elements[0]; 
			}

		protected:        
			// the actual elements of the vector
			T elements[len];

			inline void assign(const Vector & vec)
			{
				for (int i = 0; i < len; ++i)
				{
					elements[i] = vec.elements[i];
				}
			}
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
			Vector2() = default;
			explicit inline Vector2(T value)
			{
				this->elements[0] = value;
				this->elements[1] = value;
			}
			explicit inline Vector2(T x, T y)
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
			Vector3() = default;
			explicit inline Vector3(T value)
			{
				this->elements[0] = value;
				this->elements[1] = value;
				this->elements[2] = value;
			}
			explicit inline Vector3(T x, T y, T z)
			{
				this->elements[0] = x;
				this->elements[1] = y;
				this->elements[2] = z;
			}

			// copy constructor
			Vector3(const Vector<T, 3> & vec) : Vector<T, 3>(vec) {}

			// cross(a, b) = (a2 * b3 - a3 * b2,
			//                a3 * b1 - a1 * b3,
			//                a1 * b2 - a2 * b1)
			inline Vector3 Cross(Vector3<T> vec)
			{
				return Vector3(this->elements[1] * vec[2] - this->elements[2] * vec[1],
							   this->elements[2] * vec[0] - this->elements[0] * vec[2],
							   this->elements[0] * vec[1] - this->elements[1] * vec[0]);
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
			Vector4() = default;
			explicit inline Vector4(T value)
			{
				this->elements[0] = value;
				this->elements[1] = value;
				this->elements[2] = value;
				this->elements[3] = value;
			}
			explicit inline Vector4(T x, T y, T z, T w)
			{
				this->elements[0] = x;
				this->elements[1] = y;
				this->elements[2] = z;
				this->elements[3] = w;
			}

			// copy constructor
			Vector4(const Vector<T, 4> & vec) : Vector<T, 4>(vec) {}

			inline Vector3<T> Vec3()
			{
				return Vector3<T>(this->elements[0],
								  this->elements[1],
								  this->elements[2]);
			}
	};

	// defined types for usage
	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
}

#endif // _vector_h
