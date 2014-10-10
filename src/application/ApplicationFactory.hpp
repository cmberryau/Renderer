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

#include <string>
#include <memory>

namespace Renderer
{
	class ApplicationFactory
	{
		public:
			static std::shared_ptr<Application> FromFile(const std::string & file_path);

		private:
			explicit ApplicationFactory();
			~ApplicationFactory();
	};
}

#endif // _application_factory_h