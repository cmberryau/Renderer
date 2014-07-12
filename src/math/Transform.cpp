//
//  Transform.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Transform.h"

namespace Renderer
{
	void Transform::Translate(float x, float y, float z)
	{
		_position[0] += x;
		_position[1] += y;
		_position[2] += z;
	}

	void Transform::Rotate(float x, float y, float z)
	{

	}

	void Transform::Scale(float x, float y, float z)
	{
		_scale[0] = x;
		_scale[1] = y;
		_scale[2] = z;
	}

	Matrix4f Transform::ComposedMatrix()
	{
		Matrix4f translation_matrix = Matrix4f::Translate(_position[0],
														  _position[1],
														  _position[2]);
		
		return translation_matrix;
	}

	Transform::Transform() : _position(0.0f, 0.0f, 0.0f),
							 _rotation(0.0f, 0.0f, 0.0f),
							 _scale(1.0f, 1.0f, 1.0f)
    {

    }

    Transform::~Transform()
    {

    }
}