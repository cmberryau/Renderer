//
//  Scene.h
//  Renderer
//
//  Created by Christopher Berry on 18/07/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "rendering/Camera.h"
#include "objects/Object.h"

#include <vector>

namespace Renderer
{
    class Scene
    {
        public:
            static Scene * Create();
            Camera * MainCamera();
            void Draw();
            void AddObject(Object * object);
        
            ~Scene();
        
        protected:
            Scene();
        
            Camera * _main_camera;
            std::vector<Object *> objects;
    };
}