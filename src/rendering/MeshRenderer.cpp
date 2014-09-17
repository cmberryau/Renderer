//
//  MeshRenderer.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "MeshRenderer.hpp"

namespace Renderer
{
	void MeshRenderer::SetMaterial(Material * material)
	{
		_material = material;
	}

	MeshRenderer::MeshRenderer(RenderingContext * rendering_context)
	: _rendering_context(rendering_context), _mesh(nullptr)
	{

	}
}