//
//  SceneFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 01/08/2015.
//  Copyright (c) 2014-2015 Christopher Berry. All rights reserved.
//

#include "SceneFactory.hpp"

namespace Renderer
{
	std::unique_ptr<Scene> SceneFactory::SceneFromXMLNode(rapidxml::xml_node<> * scene_node)
	{
		auto scene_ptr = std::unique_ptr<Scene>(new Scene());

		return scene_ptr;
	}
}