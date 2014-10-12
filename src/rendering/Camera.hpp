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
#include "objects/ObjectAddable.hpp"
#include "rendering/RenderingContext.hpp"
#include "objects/Object.hpp"

namespace Renderer
{
	class Camera : public ObjectAddable
	{
		public:
            explicit Camera() : _projection_matrix(1.0f), _view_matrix(Matrix4f::Identity()){};
			~Camera(){};

			const Matrix4f & ViewMatrix() const;
			const Matrix4f & ProjectionMatrix() const;
        
		private:
			Matrix4f _projection_matrix;
            Matrix4f _view_matrix;
	};
}

#endif // _camera_h