//
//  Material.hpp
//  Renderer
//
//  Created by Christopher Berry on 31/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _material_h
#define _material_h

#include "Shader.hpp"

namespace Renderer
{
    class Material
    {
        public:
            void Use();
            Shader * Shader();
        
            ~Material();
            Material(class Shader * shader);
        
        protected:
            class Shader * _shader;
    };
}

#endif // _material_h