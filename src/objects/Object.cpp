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
	Object::Object() : _this(std::shared_ptr<Object>(this))
	{

	}

	void Object::Update()
	{		
		for (_children_it = _children.begin();
			 _children_it != _children.end();
			 ++_children_it)
		{
			(*_children_it)->Update(*this);
		}
	}

	void Object::Draw()
	{
		_mesh_renderer->Draw(*this);
	}

	void Object::Add(std::shared_ptr<ObjectAddable> & addable)
	{
		_children.push_back(addable);
	}

	void Object::AddMeshRenderer(std::shared_ptr<MeshRenderer> & mesh_renderer)
	{
		_mesh_renderer = mesh_renderer;
	}

	const Transform & Object::LocalTransform() const
	{
		return _transform;
	}
}