//
//  Material.cpp
//  Renderer
//
//  Created by Christopher Berry on 31/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Material.hpp"

namespace Renderer
{
    void Material::Use()
    {
        _shader->Use();
    }
    
    class Shader * Material::Shader()
    {
        return _shader;
    }
    
    Material::~Material()
    {
        
    }
    
    Material::Material(class Shader * shader)
    :_shader(shader)
    {
        
    }
}