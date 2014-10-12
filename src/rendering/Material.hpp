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
            void Use() const;
            Shader * Shader() const;
        
            ~Material();
            explicit Material(class Shader * shader);
        
        private:
            class Shader * _shader;
    };
}

#endif // _material_h