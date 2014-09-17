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
#include "objects/Object.hpp"

namespace Renderer
{
	class Camera : public IObjectAddable
	{
		public:
			Camera(RenderingContext * rendering_context);
			~Camera();

			Matrix4f ViewMatrix();
			Matrix4f ProjectionMatrix();
        
        protected:
            RenderingContext * _rendering_context;
	};
}

#endif // _camera_h