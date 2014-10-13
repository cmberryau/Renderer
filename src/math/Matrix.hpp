//
//  Matrix.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _matrix_h
#define _matrix_h

#include "Mathf.hpp"
#include "Vector.hpp"

//TODO: remove C style output
#include <stdio.h>

namespace Renderer
{
	// 
	// Renderer::Matrix<typename T, const int w, const int h> 
	//
	// Generic column-major matrix implementation, column
	// major picked to keep in line with OpenGL and DirectX
	//
	template<typename T, const int w, const int h>
	class Matrix
	{
		public:
			// constructors
			Matrix() = default;

			inline explicit Matrix(T value)
			{
				for (int i = 0; i < w; i++)
				{
					elements[i] = Vector<T, h>(value);
				}
			}

			inline explicit Matrix(const Vector<T, h> &vector)
			{
				for(int i = 0; i < w; i++)
				{
					elements[i] = vector;
				}
			}

			// copy constructor
			inline Matrix(const Matrix &rhs)
			{
				assign(rhs);
			}

            // assignment operator
            inline Matrix<T, w, h> & operator = (const Matrix<T, w, h> & matrix)
            {
                assign(matrix);
                return *this;
            }
        
			// static member functions
			static inline Matrix<T, w, h> Identity()
			{
				Matrix<T, w, h> matrix(0);
			
				for (int i = 0; i < w; i++)
				{
					matrix.elements[i][i] = 1;
				}
			
				return matrix;
			}

			// member functions

			const inline Matrix<T, w, h> Multiply(Matrix<T, w, h> factor) const
			{
				Matrix<T, w, h> result(0);

				// iterate through matrix cells
				for (int i = 0; i < w; i++)
				{
					for (int j = 0; j < h; j++)
					{
						T cell_total(0);

						// total the cell
						for (int k = 0; k < w; k++)
						{
							cell_total += elements[k][j] * factor[i][k];
						}

						result[i][j] = cell_total;
					}
				}
				return result;
			}

			// debug output
			void Print()
			{
				for(int i = 0; i < h; i++)
				{
					for (int j = 0; j < w; j++)
					{
						printf("m%d%d[%f] ", i, j, elements[j][i]);
					}
					printf("\n");
				}
				printf("\n");
			}
	
			// operators
			inline Vector<T, h> & operator [] (int n) 
			{
				return elements[n];
			}

			inline operator const T * () const 
			{
				return &elements[0][0]; 
			}
		
		protected:
		
			inline void assign(const Matrix &rhs)
			{
				for (int n=0; n<w; n++)
				{
					elements[n] = rhs.elements[n];
				}
			}
	
			Vector<T, h> elements[w];
	};

	// 
	// Renderer::Matrix4<typename T>
	//
	// Generic 4 x 4 element matrix implementation
	//
	template<typename T> 
	class Matrix4 : public Matrix <T, 4, 4>
	{
		public:
			// constructors
			Matrix4() = default;
            
			inline explicit Matrix4(T value)
			{
				this->elements[0] = Vector4<T>(value);
                this->elements[1] = Vector4<T>(value);
                this->elements[2] = Vector4<T>(value);
                this->elements[3] = Vector4<T>(value);
			}
			
			inline explicit Matrix4(const Vector4<T> & vector)
            {
                this->elements[0] = vector;
                this->elements[1] = vector;
                this->elements[2] = vector;
                this->elements[3] = vector;
            }
        
			inline explicit Matrix4(const Vector4<T> & v00,
                                    const Vector4<T> & v01,
                                    const Vector4<T> & v02,
                                    const Vector4<T> & v03)
			{
				this->elements[0] = v00;
				this->elements[1] = v01;
				this->elements[2] = v02;
				this->elements[3] = v03;
			}

			// copy constructors
			Matrix4(const Matrix4<T> & rhs)
			{
				this->assign(rhs);
			}

			Matrix4(const Matrix<T, 4, 4> & rhs) : Matrix<T, 4, 4>(rhs){}

			// static member funcitons
			static inline Matrix4<T> Translate(T x, T y, T z)
			{
				return Matrix4<T>(Vector4<T>(1.0, 0.0, 0.0, 0.0),
								  Vector4<T>(0.0, 1.0, 0.0, 0.0),
								  Vector4<T>(0.0, 0.0, 1.0, 0.0),
								  Vector4<T>(  x,   y,   z, 1.0));
			}
		
			static inline Matrix4<T> Scale(T x, T y, T z)
			{
				return Matrix4<T>(Vector4<T>(  x, 0.0, 0.0, 0.0),
								  Vector4<T>(0.0,   y, 0.0, 0.0),
								  Vector4<T>(0.0, 0.0,   z, 0.0),
								  Vector4<T>(0.0, 0.0, 0.0, 1.0));
			}
		
			// http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
			static inline Matrix4<T> Rotate(T angle, T x, T y, T z)
			{
				T x2 = x * x;
				T y2 = y * y;
				T z2 = z * z;
				
				T radians = Mathf::Deg2Rad(angle);
				
				T s = sinf(radians);
				T c = cosf(radians);
				
				T omc = (1 - c);
				
				return Matrix4<T>(Vector4<T>(c + x2 * omc, y * x * omc + z * s, z * x * omc - y * s, 0.0),
								  Vector4<T>(x * y * omc - z * s, c + y2 * omc, z * y * omc + x * s, 0.0),
								  Vector4<T>(x * z * omc + y * s, y * z * omc - x * s, c + z2 * omc, 0.0),
								  Vector4<T>(0.0, 0.0, 0.0, 1.0));
			}

			static inline Matrix4<T> Orthographic(T left, T right, T bottom, T top, T znear, T zfar)
			{
				Matrix4<T> matrix = Matrix4<T>(0);

				matrix.elements[0][0] = 2 / (right - left);
				matrix.elements[1][1] = 2 / (top - bottom);
				matrix.elements[2][2] = 2 / (zfar - znear);

				matrix.elements[3][0] = -(right + left) / (right - left);
				matrix.elements[3][1] = -(top + bottom) / (top - bottom);
				matrix.elements[3][2] = -(zfar + znear) / (zfar - znear);

				matrix.elements[3][3] = 1;

				return matrix;
			}
		
			static inline Matrix4<T>OrthoFromFOV(float vertical_fov, float aspect_ratio, float znear, float zfar)
			 {
				 float top = zfar * tan(Mathf::Deg2Rad(0.5f * vertical_fov));
				 float right = top * aspect_ratio;
				 
				 return Matrix4<T>::Orthographic(-right, right, -top, top, znear, zfar);
			 }

		
			static inline Matrix4<T> Frustrum(T left, T right, T bottom, T top, T znear, T zfar)
			{
				Matrix4<T> matrix = Matrix4<T>(0);

				matrix.elements[0][0] = (2 * znear) / (right - left);
				matrix.elements[1][1] = (2 * znear) / (top - bottom);

				// used only for asymmetric frustrums?
				//matrix.elements[2][0] = -(right + left) / (right - left);
				//matrix.elements[2][1] = -(top + bottom) / (top - bottom);

				matrix.elements[2][2] = (zfar + znear) / (zfar - znear);
				matrix.elements[2][3] = 1;

				matrix.elements[3][2] = -(2 * zfar * znear) / (zfar - znear);

				return matrix;
			}
		
			// todo : specialize for doubles
			static inline Matrix4<T> Perspective(T vertical_fov, T aspect_ratio, T znear, T zfar)
			{
				float top = znear * tan(Mathf::Deg2Rad(0.5f * vertical_fov));
				float right = top * aspect_ratio;
				
				return Matrix4<T>::Frustrum(-right, right, -top, top, znear, zfar);
			}
	};
	
	// defined types for usage
	typedef Matrix4<float> Matrix4f;
}

#endif // _matrix_h