//
//  RenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _renderingcontext_h
#define _renderingcontext_h

#include "windowing/Window.hpp"
#include "rendering/Shader.hpp"

namespace Renderer
{
    template <typename T>
    class MeshRendererType;
    
    template <typename T>
    class CameraType;
    
    template <typename T>
	class RenderingContextType
	{
		public:
            virtual void BeginScene() = 0;
            virtual void EndScene() = 0;
        
            virtual MeshRendererType<T> * MeshRenderer() = 0;
            virtual Shader * Shader() = 0;
            void SetCamera(CameraType<T> * camera)
            {
                if(camera == nullptr)
                {
                    return;
                }
                
                this->_camera = camera;
            }
        
            CameraType<T> * MainCamera()
            {
                return _camera;
            }
        
            Window * Window()
            {
                return _window;
            }
        
			virtual ~RenderingContextType<T>(){}

		protected:
			RenderingContextType<T>(){}
        
			class Window * _window;
            CameraType<T> * _camera;
	};
    
    typedef RenderingContextType<float> RenderingContext;
    typedef RenderingContextType<double> RenderingContextd;
}

#endif // _renderingcontext_h