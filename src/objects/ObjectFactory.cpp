//
//  ObjectFactory.cpp
//  Renderer
//
//  Created by Christopher Berry on 09/11/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "ObjectFactory.hpp"
#include "application/ApplicationFactory.hpp"
#include "application/ApplicationXML.hpp"

namespace Renderer
{
    std::unique_ptr<Object> ObjectFactory::ObjectFromXMLNode(rapidxml::xml_node<> * object_node)
    {
        // get the name of the object and create it
        std::string object_name("");
        if (object_node->first_attribute(ApplicationXML::kNameAttribute.c_str()) != nullptr)
        {
            object_name = std::string(object_node->first_attribute(ApplicationXML::kNameAttribute.c_str())->value());
        }
        //auto object_ptr = std::make_unique<Object>(object_name);
        auto object_ptr = std::unique_ptr<Object>(new Object(object_name));
        
        std::shared_ptr<Mesh> mesh_ptr;
        std::shared_ptr<MeshRenderer> mesh_renderer_ptr;
        
        // add the object components
        for (auto component_node = object_node->first_node();
             component_node; component_node = component_node->next_sibling())
        {
            // mesh
            if (ApplicationXML::kMeshTag.compare(component_node->name()) == 0)
            {
                // mesh path
                if (component_node->first_attribute(ApplicationXML::kPathAttribute.c_str()) != nullptr)
                {
                    std::string file_path(component_node->first_attribute(ApplicationXML::kPathAttribute.c_str())->value());
                    mesh_ptr = MeshFactory::MeshFromObjFile(file_path);
                }
            }
            
            // transform
            if(ApplicationXML::kTransformTag.compare(component_node->name()) == 0)
            {
                for(auto transform_element_node = component_node->first_node();
                    transform_element_node; transform_element_node = transform_element_node->next_sibling())
                {
                    // translation
                    if(ApplicationXML::kTranslationTag.compare(transform_element_node->name()) == 0)
                    {
                        
                    } // rotation
                    else if(ApplicationXML::kRotationTag.compare(transform_element_node->name()) == 0)
                    {
                        
                    } // scale
                    else if(ApplicationXML::kScaleTag.compare(transform_element_node->name()) == 0)
                    {
                        
                    }
                }
            }
        }
        
        return object_ptr;
    }
}