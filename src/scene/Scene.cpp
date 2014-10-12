//
//  Scene.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Scene.hpp"

namespace Renderer
{
	const Camera & Scene::MainCamera() const
	{
		return *_main_camera;
	}

	void Scene::UpdateAndDraw()
	{
		for (_objects_it = _objects.begin();
			 _objects_it != _objects.end();
			 ++_objects_it)
		{
			(*_objects_it)->Update();
			(*_objects_it)->Draw();
		}
	}

	void Scene::AddObject(std::shared_ptr<Object> & object)
	{
		_objects.push_back(object);
	}
}