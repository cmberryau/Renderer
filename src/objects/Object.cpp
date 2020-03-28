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
	: _name("Unnamed")
	{

    }

	Object::Object(std::string & name)
	: _name(name)
	{

	}
    
    Object::Object(std::string & name, Transform & transform)
    : _name(name), _transform(transform)
    {
        
    }

	bool Object::HasMesh()
	{
		return !!_mesh;
	}

	void Object::Update()
	{
		//for (auto child = _children.begin();
		//	child != _children.end();
		//	++child)
		//{
		//	(*child)->Update();
		//}
	}

	void Object::Draw(const Scene & scene)
	{
        if(!!_mesh_renderer)
        {
            _mesh_renderer->Draw(*this, scene);
        }        
	}

	void Object::AddChild(std::unique_ptr<Object> & object)
	{
		_children.push_back(std::move(object));
	}

	std::size_t Object::GetChildCount()
	{
		return _children.size();
	}

	std::vector<std::unique_ptr<Object>> & Object::GetChildren()
	{
		return _children;
	}

	void Object::AddMesh(std::shared_ptr<Mesh> & mesh)
	{
		_mesh = mesh;
	}

	void Object::AddMeshRenderer(std::unique_ptr<MeshRenderer> & mesh_renderer)
	{
        _mesh_renderer = std::move(mesh_renderer);

		if (!!_mesh)
		{
			_mesh_renderer->AddMesh(_mesh);
		}
	}

	Transform & Object::LocalTransform()
	{
		return _transform;
	}
}