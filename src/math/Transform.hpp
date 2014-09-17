//
//  Transform.hpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _transform_h
#define _transform_h

#include "Vector.hpp"
#include "Matrix.hpp"

namespace Renderer
{
    class Transform
    {
        public:
			Transform();
			~Transform();

			void Translate(float x, float y, float z);
			void SetPosition(float x, float y, float z);
        
			void Rotate(float x, float y, float z);        
			void SetRotation(float x, float y, float z);
        
			double ClampRotation(double rotation);
			float ClampRotation(float rotation);

			void Scale(float x, float y, float z);        
			void SetScale(float x, float y, float z);

			Matrix4f NormalMatrix();        
			Matrix4f ComposedMatrix();

		protected:
			Vector3f _position;
			Vector3f _rotation;
            Vector3f _scale;
        
            Matrix4f _composed_matrix;
            Matrix4f _normal_matrix;
    };
}

#endif // _transform_h
