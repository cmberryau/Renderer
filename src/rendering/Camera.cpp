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
	Camera::Camera(Object & parent,
				   float fov,
				   float aspect_ratio,
				   float zfar,
				   float znear) : 
				   ObjectAddable(parent),
				   _projection_matrix(Matrix4f::Perspective(fov, aspect_ratio, znear, zfar)),
				   _view_matrix(Matrix4f::Identity()),
				   _fov(fov), _aspect_ratio(aspect_ratio), _zfar(zfar), _znear(znear)
	{

	}

	const Matrix4f & Camera::ViewMatrix() const
	{
        return Parent().LocalTransform().ComposedMatrix();
	}

	const Matrix4f & Camera::ProjectionMatrix() const
	{
		return _projection_matrix;
	}
}