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
#include "objects/IObjectAddable.hpp"
#include "rendering/RenderingContext.hpp"

namespace Renderer
{
	template <typename T>
	class CameraType : public IObjectAddableType<T>
	{
		public:
			Matrix4<T> ViewMatrix()
			{
				return this->_parent_object->LocalTransform()->ComposedMatrix();
			}

			Matrix4<T> ProjectionMatrix()
			{
				return Matrix4<T>::Perspective(T(75.0), T(1.33), T(1.0), T(500.0));
			}

			CameraType<T>(RenderingContextType<T> * rendering_context)
            : _rendering_context(rendering_context)
			{
                
			}

			~CameraType<T>()
			{

			}
        
        protected:
            RenderingContextType<T> * _rendering_context;
	};
    
	typedef CameraType<float> Camera;
	typedef CameraType<double> Camerad;
}

#endif // _camera_h