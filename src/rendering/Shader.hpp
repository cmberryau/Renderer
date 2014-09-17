//
//  Shader.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _shader_h
#define _shader_h

#include <string>

namespace Renderer
{
    class Shader
    {
        public:
            virtual void Use() = 0;
        
            virtual Shader * Compile(std::string & vertex_shader_source,
                                     std::string & fragment_shader_source) = 0;
        
            virtual Shader * Compile(std::string & vertex_shader_source,
                                     std::string & geometry_shader_source,
                                     std::string & fragment_shader_source) = 0;
        
            virtual ~Shader(){}
        
        protected:
            Shader(){};
    };
}

#endif // _shader_h