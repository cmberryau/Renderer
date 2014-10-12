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
			explicit Scene(){};
			~Scene(){};
			
			void UpdateAndDraw();
			void AddObject(std::shared_ptr<Object> & object);

			std::shared_ptr<Camera> & MainCamera();
			void SetMainCamera(std::shared_ptr<Camera> & camera);
        
        private:
            std::shared_ptr<Camera> _main_camera;
			std::vector<std::shared_ptr<Object>> _objects;
			std::vector<std::shared_ptr<Object>>::iterator _objects_it;
    };
}

#endif // _scene_h