//
//  MeshRenderer.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _shader_factory_h
#define _shader_factory_h

#include "OpenGL/OpenGLRenderingContext.hpp"
#include "OpenGL/OpenGLShader.hpp"

#include "OpenGLES/OpenGLESRenderingContext.hpp"
#include "OpenGLES/OpenGLESShader.hpp"

#include <string>
#include <memory>

namespace Renderer
{
    class ShaderFactory
    {
        public:
            static std::shared_ptr<Shader> Create(std::string & vertex_shader_source,
												  std::string & geometry_shader_source,
												  std::string & fragment_shader_source);
        
			static std::shared_ptr<Shader> Create(std::string & vertex_shader_source,
												  std::string & fragment_shader_source);
        
        private:
			explicit ShaderFactory();
			~ShaderFactory();
    };
}

#endif // _shader_factory_h