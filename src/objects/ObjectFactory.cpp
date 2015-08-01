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
        std::string name("Object");
        Transform transform;
        std::shared_ptr<Mesh> mesh_ptr;
        
        // add the object components
        for (auto component_node = object_node->first_node();
             component_node; component_node = component_node->next_sibling())
        {
            // name
            if (ApplicationXML::kNameTag.compare(component_node->name()) == 0)
            {
                if(component_node->value() != nullptr)
                {
                    name = std::string(component_node->value());
                }
            }
            
            // mesh
            if (ApplicationXML::kMeshTag.compare(component_node->name()) == 0)
            {
                mesh_ptr = ProcessMeshXMLNode(component_node);
            }
            
            // transform
            if(ApplicationXML::kTransformTag.compare(component_node->name()) == 0)
            {
                transform = ProcessTransformXMLNode(component_node);
            }
        }
        
        auto object_ptr = std::unique_ptr<Object>(new Object(name, transform));

		if (!!mesh_ptr)
		{
			object_ptr->AddMesh(mesh_ptr);
		}		
        
        return object_ptr;
    }
    
    std::shared_ptr<Mesh> ObjectFactory::ProcessMeshXMLNode(rapidxml::xml_node<> * mesh_node)
    {
        std::shared_ptr<Mesh> mesh_ptr;
        
        // run through mesh children
        for(auto mesh_child_node = mesh_node->first_node();
            mesh_child_node; mesh_child_node = mesh_child_node->next_sibling())
        {
            if(mesh_child_node->value() != nullptr)
            {
                // mesh path
                if(ApplicationXML::kPathTag.compare(mesh_child_node->name()) == 0)
                {
                    if(!!mesh_ptr)
                    {
                        throw std::runtime_error("Mesh cannot have multiple paths");
                    }
                    
                    std::string file_path(mesh_child_node->value());
                    mesh_ptr = MeshFactory::MeshFromObjFile(file_path);
                }
            }
        }
        
        return mesh_ptr;
    }
    
    Transform ObjectFactory::ProcessTransformXMLNode(rapidxml::xml_node<> * transform_node)
    {
        Transform transform;
        
        for(auto transform_element_node = transform_node->first_node();
            transform_element_node; transform_element_node = transform_element_node->next_sibling())
        {
            // position
            if(ApplicationXML::kPositionTag.compare(transform_element_node->name()) == 0)
            {
				auto vec3f = ProcessVector3XMLNode(transform_element_node);
				transform.SetPosition(vec3f);
            } // rotation
            else if(ApplicationXML::kRotationTag.compare(transform_element_node->name()) == 0)
            {
				auto vec3f = ProcessVector3XMLNode(transform_element_node);
				transform.SetRotation(vec3f);
            } // scale
            else if(ApplicationXML::kScaleTag.compare(transform_element_node->name()) == 0)
            {
				auto vec3f = ProcessVector3XMLNode(transform_element_node);
				transform.SetScale(vec3f);
            }
        }

        return transform;
    }

	Vector3f ObjectFactory::ProcessVector3XMLNode(rapidxml::xml_node<> * vector_node)
	{
		Vector3f vector;

		for (auto axis_node = vector_node->first_node();
			axis_node; axis_node = axis_node->next_sibling())
		{
			if (ApplicationXML::kXTag.compare(axis_node->name()) == 0)
			{
				if (axis_node->value() != nullptr)
				{
					vector[0] = std::stof(axis_node->value());
				}
			}

			if (ApplicationXML::kYTag.compare(axis_node->name()) == 0)
			{
				if (axis_node->value() != nullptr)
				{
					vector[1] = std::stof(axis_node->value());
				}
			}

			if (ApplicationXML::kZTag.compare(axis_node->name()) == 0)
			{
				if (axis_node->value() != nullptr)
				{
					vector[2] = std::stof(axis_node->value());
				}
			}
		}

		return vector;
	}
}