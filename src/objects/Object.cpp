//
//  Object.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Object.h"

namespace Renderer
{
	Transform * Object::LocalTransform()
	{
		return & _transform;
	}

	void Object::AddMesh(Mesh * mesh)
	{
		if (mesh == nullptr)
			return;

		_mesh = mesh;
	}

	void Object::AddMeshRenderer(MeshRenderer * mesh_renderer)
	{
		if (mesh_renderer == nullptr)
			return;
        
		_mesh_renderer = mesh_renderer;
        _mesh_renderer->Store(_mesh);
	}
    
    void Object::Draw()
    {
        _mesh_renderer->Draw(this);
    }

	Object::Object() : _mesh(nullptr),
					   _mesh_renderer(nullptr)
    {
        
    }
    
    Object::~Object()
    {
		delete _mesh;
		delete _mesh_renderer;
    }
}