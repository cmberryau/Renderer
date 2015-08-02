//
//  RenderingContext.hpp
//  Renderer
//
//  Created by Christopher Berry on 05/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _renderingcontext_h
#define _renderingcontext_h

#include "rendering/MeshRenderer.hpp"

namespace Renderer
{    
	class RenderingContext
	{
		public:
			virtual ~RenderingContext(){};

			virtual void BeginScene() const = 0;
			virtual void EndScene() const = 0;

			virtual std::unique_ptr<MeshRenderer> CreateMeshRenderer() const = 0;
			virtual std::shared_ptr<Material> DefaultMaterial() const = 0;

			virtual std::shared_ptr<Shader> CreateShader(std::string & vertex_source,
														 std::string & fragment_source) const = 0;

			virtual std::shared_ptr<Shader> CreateShader(std::string & vertex_source,
													     std::string & geometry_source,
													     std::string & fragment_source) const = 0;
        
        protected:
			explicit RenderingContext(){};
	};
}

#endif // _renderingcontext_h