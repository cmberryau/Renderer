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
    class MeshRenderer;
    class Camera;
    
	class RenderingContext
	{
		public:
            virtual void BeginScene() = 0;
            virtual void EndScene() = 0;
        
            virtual MeshRenderer * MeshRenderer() = 0;
            virtual Shader * Shader() = 0;
			void SetCamera(Camera * camera);
        
			Camera * MainCamera();        
			Window * Window();
        
			virtual ~RenderingContext(){}

		protected:
			RenderingContext(){}
        
			class Window * _window;
            Camera * _camera;
	};
}

#endif // _renderingcontext_h