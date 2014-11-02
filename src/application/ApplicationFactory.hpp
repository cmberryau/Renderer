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
			static const std::string kApplicationTag;
			static const std::string kSceneTag;
			static const std::string kObjectTag;
			static const std::string kMeshTag;

			static const std::string kNameAttribute;
			static const std::string kPathAttribute;

			static void ProcessObjectXMLNode(rapidxml::xml_node<> * object_node,
											 std::vector<std::unique_ptr<Object>> & objects);

			explicit ApplicationFactory();
			~ApplicationFactory();
	};
}

#endif // _application_factory_h