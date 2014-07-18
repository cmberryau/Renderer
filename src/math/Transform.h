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
    template<typename T>
    class Transform
    {
        public:
			void Translate(T x, T y, T z)
            {
                Matrix4<T> translation_matrix;
                
                _position[0] += x;
                _position[1] += y;
                _position[2] += z;

                translation_matrix = Matrix4<T>::Translate(x, y, z);
                
                _composed_matrix = _composed_matrix.Multiply(translation_matrix);
            }
        
            void SetPosition(T x, T y, T z)
            {
                Matrix4<T> translation_matrix = Matrix4<T>::Translate(-_position[0] + x,
                                                                      -_position[1] + y,
                                                                      -_position[2] + z);
                
                _composed_matrix = _composed_matrix.Multiply(translation_matrix);
                
                _position[0] = x;
                _position[1] = y;
                _position[2] = z;
            }
        
			void Rotate(T x, T y, T z)
            {
                Matrix4<T> rotation_matrix[3];
                
                _rotation[0] = x;
                _rotation[1] = y;
                _rotation[2] = z;
                
                for(int i=0; i<3; i++)
                {
                    Vector3<T> rotation_axes(T(0));
                    rotation_axes[i] = T(1);
                    
                    rotation_matrix[i] = Matrix4<T>::Rotate(_rotation[i],
                                                            rotation_axes[0],
                                                            rotation_axes[1],
                                                            rotation_axes[2]);
                    
                    _composed_matrix = _composed_matrix.Multiply(rotation_matrix[i]);
                }
            }
        
            void SetRotation(T x, T y, T z)
            {
                Matrix4<T> rotation_matrix[3];
                Vector3<T> rotation(x, y, z);
                
                for(int i=0; i<3; i++)
                {
                    Vector3<T> rotation_axes(T(0));
                    rotation_axes[i] = T(1);
                    
                    rotation_matrix[i] = Matrix4<T>::Rotate(-_rotation[i] + rotation[i],
                                                            rotation_axes[0],
                                                            rotation_axes[1],
                                                            rotation_axes[2]);
                    
                    _composed_matrix = _composed_matrix.Multiply(rotation_matrix[i]);
                    _rotation[i] = rotation[i];
                }
            }
        
			void Scale(T x, T y, T z)
            {
                Matrix4<T> scale_matrix;
                
                _scale[0] += x;
                _scale[1] += y;
                _scale[2] += z;
                
                _composed_matrix = _composed_matrix.Multiply(scale_matrix);
            }
        
            void SetScale(T x, T y, T z)
            {
                Matrix4<T> scale_matrix = Matrix4<T>::Scale(-_scale[0] + x,
                                                            -_scale[1] + y,
                                                            -_scale[2] + z);
                
                _scale[0] = x;
                _scale[1] = y;
                _scale[2] = z;
                
                _composed_matrix = _composed_matrix.Multiply(scale_matrix);
            }

			Matrix4<T> ComposedMatrix()
            {
                //_composed_matrix = Matrix4<T>::Identity();
                
                return _composed_matrix;
            }

            Transform<T>(): _position(T(0), T(0), T(0)),
                            _rotation(T(0), T(0), T(0)),
                               _scale(T(1), T(1), T(1)),
                            _composed_matrix(Matrix4<T>::Identity())
        
            {
                
            }
        
            ~Transform<T>()
            {
                
            }

		protected:
			Vector3<T> _position;
			Vector3<T> _rotation;
            Vector3<T> _scale;
        
            Matrix4<T> _composed_matrix;
    };
    
    typedef Transform<float> Transformf;
}

#endif // _transform_h
