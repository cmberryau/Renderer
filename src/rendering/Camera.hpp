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

namespace Renderer
{
	class Camera
	{
		public:
			static Camera * MainCamera();
			Matrix4f ViewMatrix();
			Matrix4f ProjectionMatrix();

			Camera();
			~Camera();

		protected:
			TransformType<float> _transform;
	};
}

#endif // _camera_h