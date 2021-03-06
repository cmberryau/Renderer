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
	void Material::Use() const
	{
		_shader->Use();
	}

	const Shader * Material::GetShader() const
	{
		return _shader.get();
	}

	Material::Material(std::shared_ptr<Shader> shader) : _shader(shader)
	{

	}
}