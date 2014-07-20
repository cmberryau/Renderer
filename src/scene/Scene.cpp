//
//  Scene.cpp
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Scene.h"

namespace Renderer
{
    Scene * Scene::Create()
    {
        return new Scene();
    }
    
    Camera * Scene::MainCamera()
    {
        return _main_camera;
    }
    
    void Scene::Draw()
    {
        for(int i=0; i<objects.size(); i++)
        {
            objects[i]->Draw();
        }
    }
    
    void Scene::AddObject(Object * object)
    {
        objects.push_back(object);
    }
    
    Scene::~Scene()
    {
        
    }
    
    Scene::Scene() : _main_camera(nullptr)
    {
        
    }
}