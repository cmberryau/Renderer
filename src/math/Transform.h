//
//  Transform.h
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _transform_h
#define _transform_h

#include "Vector.h"
#include "Matrix.h"

namespace Renderer
{
    class Transform
    {
        public:
			void Translate(float x, float y, float z);
			void Rotate(float x, float y, float z);
			void Scale(float x, float y, float z);

			Matrix4f ComposedMatrix();

            Transform();
            ~Transform();

		protected:
			Vector3f _position;
			Vector3f _rotation;
			Vector3f _scale;
    };
}

#endif // _transform_h
