//
//  ApplicationFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _application_factory_h
#define _application_factory_h

#include "application/Application.hpp"
#include "utility/rapidxml/rapidxml.hpp"

#include <string>
#include <memory>

namespace Renderer
{
	class ApplicationFactory
	{
        public:
			static std::shared_ptr<Application> FromFile(const std::string & file_path);

		private:
			static std::unique_ptr<Scene> ProcessSceneXMLNode(rapidxml::xml_node<> * scene_node);
			static std::vector<std::unique_ptr<Object>> CreateSceneObjects(rapidxml::xml_node<> * scene_node);
			static void ProcessObjectXMLNode(rapidxml::xml_node<> * object_node,
											 std::vector<std::unique_ptr<Object>> & objects);
			static void ProcessObjectXMLNode(rapidxml::xml_node<> * object_node,
											 std::unique_ptr<Object> & parent);
			static void PostProcessObjectsRecursive(std::vector<std::unique_ptr<Object>> & parents);
			static void PostProcessObjectRecursive(std::unique_ptr<Object> & object);
			
			explicit ApplicationFactory();
			~ApplicationFactory();
	};
}

#endif // _application_factory_h