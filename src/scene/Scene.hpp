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
			void AddObject(std::unique_ptr<Object> & object);

			const Camera & MainCamera() const;
			void SetMainCamera(Camera * camera);
        
        private:
            Camera * _main_camera;
        
			std::vector<std::unique_ptr<Object>> _objects;
			std::vector<std::unique_ptr<Object>>::iterator _objects_it;
    };
}

#endif // _scene_h