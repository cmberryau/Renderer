//
//  Camera.hpp
//  Renderer
//
//  Created by Christopher Berry on 12/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _camera_h
#define _camera_h

#include "math/Transform.hpp"
#include "objects/Object.hpp"
#include "objects/ObjectAddable.hpp"

namespace Renderer
{
	class Camera : public ObjectAddable
	{
		public:
			explicit Camera(Object & parent,
							float fov,
							float aspect_ratio,
							float zfar,
							float znear);
			~Camera(){};

			const Matrix4f & ViewMatrix() const;
			const Matrix4f & ProjectionMatrix() const;

		private:
			Matrix4f _projection_matrix, _view_matrix;
			float _fov, _aspect_ratio, _zfar, _znear;
	};
}

#endif // _camera_h