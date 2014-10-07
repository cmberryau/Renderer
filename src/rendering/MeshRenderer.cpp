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
	void MeshRenderer::AddMaterial(Material * material)
	{
		_material = material;
	}
    
    void MeshRenderer::AddMaterial(const std::shared_ptr<Material> & material_ptr)
    {
        _material_ptr = material_ptr;
    }

	MeshRenderer::MeshRenderer(RenderingContext * rendering_context)
	: _rendering_context(rendering_context), _mesh(nullptr)
	{

	}
    
    MeshRenderer::MeshRenderer(const std::shared_ptr<RenderingContext> & rendering_context_ptr)
    : _rendering_context_ptr(rendering_context_ptr)
    {
        
    }
    
    const Mesh & MeshRenderer::GetMesh() const
    {
        return *_mesh_ptr;
    }
    
    const Material & MeshRenderer::GetMaterial() const
    {
        return *_material_ptr;
    }
    
    const RenderingContext & MeshRenderer::GetRenderingContext() const
    {
        return *_rendering_context_ptr;
    }
    
    bool MeshRenderer::HasMesh() const
    {
        return !!_mesh_ptr;
    }
    
    bool MeshRenderer::HasMaterial() const
    {
        return !!_material_ptr;
    }
    
    bool MeshRenderer::HasRenderingContext() const
    {
        return !!_rendering_context_ptr;
    }
    
    void MeshRenderer::SetMesh(const std::shared_ptr<Mesh> & mesh_ptr)
    {
        _mesh_ptr = mesh_ptr;
    }
    
    void MeshRenderer::SetMaterial(const std::shared_ptr<Material> & material_ptr)
    {
        _material_ptr = material_ptr;
    }
    
    void MeshRenderer::SetRenderingContext(const std::shared_ptr<RenderingContext> & rendering_context_ptr)
    {
        _rendering_context_ptr = rendering_context_ptr;
    }
}