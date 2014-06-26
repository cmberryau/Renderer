//
//  Matrix.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _matrix_h
#define _matrix_h

#include <stdio.h>

#include "Vector.h"

namespace Renderer
{
	template<typename T, const int w, const int h> 
	class Matrix
	{
		public:
			operator const T * () const { return &elements[0][0]; }

			Matrix(){};

			Matrix(T value)
			{
				for (int i = 0; i < w; i++)
				{
					elements[i] = value;
				}
			}

            Matrix(const Matrix &that);

            static Matrix<T, w, h> identity();

			void Print()
			{
				for(int i = 0; i < h; i++)
				{
					for (int j = 0; j < w; j++)
					{
						printf("[%f]", elements[i][j]);
					}
					printf("\n");
				}
			}
        
		protected:
            void assign(const Matrix &that);
        
			Vector<T, h> elements[w];
	};

	template<typename T> 
	class Matrix4 : public Matrix <T, 4, 4>
	{
		public:
			Matrix4(){};
            Matrix4(const Matrix4<T> & that);
            Matrix4(const Matrix<T, 4, 4> & that);
	};
	
	typedef Matrix4<float> Matrix4f;
}

#endif // _matrix_h

namespace Renderer
{
	// Matrix
	template <typename T, const int w, const int h>
	Matrix<T, w, h>::Matrix(const Matrix<T, w, h> & that)
	{
		assign(that);
	}

	template <typename T, const int w, const int h>
	void Matrix<T, w, h>::assign(const Matrix<T, w, h> & that)
	{
		for (int n=0; n<w; n++)
		{
			elements[n] = that.elements[n];
		}
	}

	template <typename T, const int w, const int h>
	Matrix<T, w, h> Matrix<T, w, h>::identity()
	{
		Matrix<T, w, h> matrix(0);

		for (int i=0; i<w; i++)
		{
			matrix.elements[i][i] = 1;
		}

		return matrix;
	}

	// Matrix4
	template <typename T>
	Matrix4<T>::Matrix4(const Matrix4<T> & that)
	{
		assign(that);
	}

	template <typename T>
	Matrix4<T>::Matrix4(const Matrix<T, 4, 4> & that) : Matrix<T, 4, 4>(that)
	{
		
	}
}