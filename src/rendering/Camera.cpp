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
	Matrix4f Camera::ViewMatrix()
	{
		return this->_parent_object->LocalTransform().ComposedMatrix();
	}

	const Matrix4f & Camera::ProjectionMatrix() const
	{
		return _projection_matrix;
	}
}