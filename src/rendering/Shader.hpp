//
//  Shader.hpp
//  Renderer
//
//  Created by Christopher Berry on 30/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _shader_h
#define _shader_h

namespace Renderer
{
    class Shader
    {
        public:
            virtual void Use() = 0;
            virtual Shader * Compile(char * vertex_shader_source,
                                     char * geometry_shader_source,
                                     char * fragment_shader_source) = 0;
        
            virtual ~Shader(){}
        
        protected:
            Shader(){};
    };
}

#endif // _shader_h