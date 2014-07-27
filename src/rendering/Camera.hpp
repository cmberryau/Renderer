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
	template <typename T>
	class CameraType
	{
		public:
			static CameraType<T> * MainCamera()
			{
				return nullptr;
			}

			Matrix4<T> ViewMatrix()
			{
				return Matrix4<T>::Identity();
			}

			Matrix4<T> ProjectionMatrix()
			{
				return Matrix4<T>::Perspective(T(75.0), T(1.33), T(1.0), T(500.0));
			}

			CameraType<T>() : _transform(nullptr)
			{

			}

			~CameraType<T>()
			{

			}

		protected:
			TransformType<T> _transform;
	};

	typedef CameraType<float> Camera;
	typedef CameraType<double> Camerad;
}

#endif // _camera_h