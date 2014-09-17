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
	Object::~Object()
	{
		for (std::size_t i = 0; i < _addables.size(); ++i)
		{
			delete _addables[i];
		}
	}

	Object::Object() : _mesh_renderer(nullptr)
	{

	}

	Transform * Object::LocalTransform()
	{
		return &_transform;
	}

	void Object::Add(IObjectAddable * object)
	{
		if (object == nullptr)
			return;

		_addables.push_back(object);
		object->Added(this);
	}

	void Object::AddMeshRenderer(MeshRenderer * mesh_renderer)
	{
		if (mesh_renderer == nullptr)
			return;

		_mesh_renderer = mesh_renderer;
	}

	void Object::Update()
	{
		for (std::size_t i = 0; i < _addables.size(); ++i)
		{
			if (_addables[i] == nullptr)
			{
				return;
			}

			_addables[i]->Update(this);
		}
	}

	void Object::Draw()
	{
		if (_mesh_renderer != nullptr)
		{
			_mesh_renderer->Draw(this);
		}
	}
}