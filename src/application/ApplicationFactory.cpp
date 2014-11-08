//
//  ApplicationFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 16/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ApplicationFactory.hpp"

#ifdef EMSCRIPTEN
#include "application/EmscriptenApplication.hpp"
#endif

namespace Renderer
{
	const std::string ApplicationFactory::kApplicationTag = "Application";
	const std::string ApplicationFactory::kSceneTag = "Scene";
	const std::string ApplicationFactory::kObjectTag = "Object";
	const std::string ApplicationFactory::kMeshTag = "Mesh";

	const std::string ApplicationFactory::kNameAttribute = "name";
	const std::string ApplicationFactory::kPathAttribute = "path";

	std::shared_ptr<Application> ApplicationFactory::FromFile(const std::string & file_path)
    {
        std::string window_name("Renderer");
        
        // temporary code		
		auto window = std::make_shared<Window>(640, 480, window_name);
#ifndef EMSCRIPTEN
        auto rendering_context = std::make_shared<OpenGLRenderingContext>(*window);
#else
		auto rendering_context = std::make_shared<OpenGLESRenderingContext>(*window);
#endif
        auto event_listener = std::make_shared<EventListener>();
        
#ifdef EMSCRIPTEN
        auto app = std::make_shared<EmscriptenApplication>(window, rendering_context, event_listener);
#else
		auto app = std::make_shared<Application>(window, rendering_context, event_listener);
#endif     

        auto content = IO::ReadFile(file_path);
        
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

		std::vector<std::unique_ptr<Object>> objects;

		auto root_node = doc.first_node(kApplicationTag.c_str());
        if(root_node)
        {
            for(auto scene_node = root_node->first_node(kSceneTag.c_str()); 
				scene_node; scene_node = scene_node->next_sibling())
            {
                for(auto object_node = scene_node->first_node(kObjectTag.c_str()); 
					object_node; object_node = object_node->next_sibling())
                {
					ProcessObjectXMLNode(object_node, objects);
                }
            }
        }
        
		return app;
	}

	// processes an xml node that refers to an object
	void ApplicationFactory::ProcessObjectXMLNode(rapidxml::xml_node<> * object_node,
												  std::vector<std::unique_ptr<Object>> & objects)
	{
		// get the name of the object and create it
		std::string object_name("");
		if (object_node->first_attribute(kNameAttribute.c_str()) != nullptr)
		{
			object_name = std::string(object_node->first_attribute(kNameAttribute.c_str())->value());
		}
		//auto object_ptr = std::make_unique<Object>(object_name);
        auto object_ptr = std::unique_ptr<Object>(new Object(object_name));
		
		// add the object components
		for (auto component_node = object_node->first_node();
			 component_node; component_node = component_node->next_sibling())
		{
			// mesh
			if (kMeshTag.compare(component_node->name()) == 0)
			{
				// mesh path
				if (component_node->first_attribute(kPathAttribute.c_str()) != nullptr)
				{
					std::string file_path(component_node->first_attribute(kPathAttribute.c_str())->value());
					auto mesh_ptr = MeshFactory::MeshFromObjFile(file_path);
				}
			}
		}

		// add it to the vector of objects
		objects.push_back(std::move(object_ptr));

		// process any child objects
		for (auto child_node = object_node->first_node(kObjectTag.c_str());
			child_node; child_node = child_node->next_sibling())
		{
			ProcessObjectXMLNode(child_node, objects);
		}
	}
}