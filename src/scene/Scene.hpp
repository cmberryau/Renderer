//
//  Scene.hpp
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _scene_h
#define _scene_h

#include "rendering/Camera.hpp"
#include "objects/Object.hpp"

#include <vector>

namespace Renderer
{
    template <typename T>
    class SceneType
    {
        public:        
            Camera * MainCamera()
            {
                return _main_camera;
            }
        
            void UpdateAndDraw()
            {
                for(int i=0; i<objects.size(); i++)
                {
                    objects[i]->Update();
                    objects[i]->Draw();
                }
            }
        
            void AddObject(ObjectType<T> * object)
            {
                objects.push_back(object);
            }

			SceneType<T>() : _main_camera(nullptr)
			{

			}

            ~SceneType<T>()
            {
                
            }
        
        protected:        
            Camera * _main_camera;
            std::vector<ObjectType<T> *> objects;
    };
    
    typedef SceneType<float> Scene;
    typedef SceneType<double> Scened;
}

#endif // _scene_h