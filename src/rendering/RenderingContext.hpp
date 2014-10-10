//
//  RenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _renderingcontext_h
#define _renderingcontext_h

namespace Renderer
{    
	class RenderingContext
	{
		public:
			virtual void BeginScene() const = 0;
			virtual void EndScene() const = 0;
			
			virtual ~RenderingContext(){};			
        
        protected:
			explicit RenderingContext(){};
	};
}

#endif // _renderingcontext_h