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
    class Scene
    {
        public:
			Scene();
			~Scene();

			Camera * MainCamera();
			void UpdateAndDraw();        
			void AddObject(Object * object);
        
        protected:        
            Camera * _main_camera;
            std::vector<Object *> _objects;
    };
}

#endif // _scene_h