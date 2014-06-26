//
//  Matrix.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include <stdio.h>
#include "Matrix.h"

namespace Renderer
{
    // Matrix
    
    template <typename T, const int w, const int h> Matrix<T, w, h>::Matrix(const Matrix<T, w, h> &that)
    {
        assign(that);
    }
    
    template <typename T, const int w, const int h> void Matrix<T, w, h>::assign(const Matrix<T, w, h> &that)
    {
        for(int n=0; n<w; n++)
        {
            elements[n] = that.elements[n];
        }
    }
    
    template <typename T, const int w, const int h> Matrix<T, w, h> Matrix<T, w, h>::identity()
    {
        Matrix<T, w, h> matrix(0);
        
        for(int i=0; i<w; i++)
        {
            matrix[i][i] = 1;
        }
        
        return matrix;
    }
    
    // Matrix4
    
	template <typename T> Matrix4<T>::Matrix4(const Matrix4<T> & that)
    {
        printf("hello");
    }
    
    template <typename T> Matrix4<T>::Matrix4(const Matrix<T, 4, 4> & that)
    {
        printf("hello");        
    }
    
	template <typename T> Matrix4<T>::Matrix4(T e00, T e01, T e02, T e03,
											  T e10, T e11, T e12, T e13,
											  T e20, T e21, T e22, T e23,
											  T e30, T e31, T e32, T e33)
	{
        this->elements[0].x = e00; this->elements[0].y = e10;
		this->elements[1].x = e01; this->elements[1].y = e11;
		this->elements[2].x = e02; this->elements[2].y = e12;
		this->elements[3].x = e03; this->elements[3].y = e13;
        this->elements[0].z = e20; this->elements[0].w = e30;
        this->elements[1].z = e21; this->elements[1].w = e31;
        this->elements[2].z = e22; this->elements[2].w = e32;
        this->elements[3].z = e23; this->elements[3].w = e33;
	}
}