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
			explicit Transform();
			~Transform();

			void Translate(Vector3f & translation);
			void Translate(float x, float y, float z);
			void SetPosition(Vector3f & position);
			void SetPosition(float x, float y, float z);
			const Vector3f & Position() const;
        
			void Rotate(Vector3f & rotate);
			void Rotate(float x, float y, float z);
			void SetRotation(Vector3f & rotation);
			void SetRotation(float x, float y, float z);
			const Vector3f & Rotation() const;

			void Scale(Vector3f & scale);
			void Scale(float x, float y, float z);
			void SetScale(Vector3f & scale);
			void SetScale(float x, float y, float z);
			const Vector3f & Scale() const;

			const Matrix4f & NormalMatrix() const;
			const Matrix4f & ComposedMatrix() const;

		private:
			double ClampRotation(double rotation);
			float ClampRotation(float rotation);

			Vector3f _position;
			Vector3f _rotation;
            Vector3f _scale;
        
            Matrix4f _composed_matrix;
            Matrix4f _normal_matrix;
    };
}

#endif // _transform_h
