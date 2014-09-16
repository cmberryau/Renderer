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
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Camera * Scene::MainCamera()
	{
		return _main_camera;
	}

	void Scene::UpdateAndDraw()
	{
		for (int i = 0; i<_objects.size(); i++)
		{
			_objects[i]->Update();
			_objects[i]->Draw();
		}
	}

	void Scene::AddObject(Object * object)
	{
		_objects.push_back(object);
	}
}