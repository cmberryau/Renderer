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
        Matrix(){};
        Matrix(T value)
        {
            for (int i = 0; i < w; i++)
            {
                elements[i] = value;
            }
        }
        Matrix(const Matrix &that)
        {
            assign(that);
        }
        Matrix(const Vector<T, h> &vector)
        {
            for(int i=0; i<w; i++)
            {
                elements[i] = vector;
            }
        }

		// member functions
        static Matrix<T, w, h> Identity()
        {
            Matrix<T, w, h> matrix(0);
            
            for (int i=0; i<w; i++)
            {
                matrix.elements[i][i] = 1;
            }
            
            return matrix;
        }

		// debug member functions
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
        operator const T * () const { return &elements[0][0]; }
        
		protected:
        
        void assign(const Matrix &that)
        {
            for (int n=0; n<w; n++)
            {
                elements[n] = that.elements[n];
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
        Matrix4(){};
        Matrix4(const Matrix4<T> & that)
        {
            this->assign(that);
        }
        Matrix4(const Matrix<T, 4, 4> & that) : Matrix<T, 4, 4> (that){}
        Matrix4(const Vector4<T> & vector) : Matrix<T, 4, 4> (vector){}
        Matrix4(const Vector4<T> & v00,
                const Vector4<T> & v01,
                const Vector4<T> & v02,
                const Vector4<T> & v03)
        {
            this->elements[0] = v00;
            this->elements[1] = v01;
            this->elements[2] = v02;
            this->elements[3] = v03;
        }
        
		// member funcitons
        static Matrix4<T> Translate(T x, T y, T z)
        {
            return Matrix4<T>(Vector4<T>(1.0, 0.0, 0.0, 0.0),
                              Vector4<T>(0.0, 1.0, 0.0, 0.0),
                              Vector4<T>(0.0, 0.0, 1.0, 0.0),
                              Vector4<T>(  x,   y,   z, 1.0f));
        }
	};
	
	// defined types for usage
	typedef Matrix4<float> Matrix4f;
}

#endif // _matrix_h