//
//  Camera.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Camera.hpp"

namespace Renderer
{
	Camera::Camera(RenderingContext * rendering_context)
		: _rendering_context(rendering_context)
	{

	}

	Camera::~Camera()
	{

	}

	Matrix4f Camera::ViewMatrix()
	{
		return this->_parent_object->LocalTransform()->ComposedMatrix();
	}

	Matrix4f Camera::ProjectionMatrix()
	{
		return Matrix4f::Perspective(75.0f, 1.33f, 1.0f, 500.0f);
	}
}