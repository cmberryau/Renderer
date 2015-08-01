//
//  SceneFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 01/08/2015.
//  Copyright (c) 2014-2015 Christopher Berry. All rights reserved.
//

#ifndef _scene_factory_h
#define _scene_factory_h

#include "scene/Scene.hpp"
#include "utility/rapidxml/rapidxml.hpp"

#include <memory>

namespace Renderer
{
	class SceneFactory
	{
		public:
			static std::unique_ptr<Scene> SceneFromXMLNode(rapidxml::xml_node<> * scene_node);
	};
}

#endif // _scene_factory_h