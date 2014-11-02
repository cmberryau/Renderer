//
//  Object.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/10/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Object.hpp"

namespace Renderer
{	
	Object::Object()
	: _name("UnnamedObject")
	{

	}

	Object::Object(std::string name)
	: _name(name)
	{

	}

	void Object::Update()
	{		
		for (_children_it = _children.begin();
			 _children_it != _children.end();
			 ++_children_it)
		{
			(*_children_it)->Update();
		}
	}

	void Object::Draw(const Scene & scene)
	{
        if(!!_mesh_renderer)
        {
            _mesh_renderer->Draw(*this, scene);
        }        
	}

	void Object::Add(std::unique_ptr<ObjectAddable> & addable)
	{
        addable->Added(this);
        _children.push_back(std::move(addable));
	}

	void Object::AddMeshRenderer(std::unique_ptr<MeshRenderer> & mesh_renderer)
	{
        _mesh_renderer = std::move(mesh_renderer);
	}

	Transform & Object::LocalTransform()
	{
		return _transform;
	}
}