//
//  ObjectFactory.hpp
//  Renderer
//
//  Created by Christopher Berry on 09/11/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _object_factory_h
#define _object_factory_h

#include <objects/Object.hpp>

#include "utility/rapidxml/rapidxml.hpp"

namespace Renderer
{
    class ObjectFactory
    {
        public:
            static std::unique_ptr<Object> ObjectFromXMLNode(rapidxml::xml_node<> * object_node);
        
        private:
            static std::shared_ptr<Mesh> ProcessMeshXMLNode(rapidxml::xml_node<> * mesh_node);
            static Transform ProcessTransformXMLNode(rapidxml::xml_node<> * transform_node);
			static Vector3f ObjectFactory::ProcessVector3XMLNode(rapidxml::xml_node<> * vector_node);
        
            explicit ObjectFactory();
            ~ObjectFactory();
    };
}

#endif // _object_factory_h