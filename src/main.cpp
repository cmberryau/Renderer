//
//  main.cpp
//  Renderer
//
//  Created by Christopher Berry on 9/06/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "application/ApplicationFactory.hpp"

// for memory leak detection on windows
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace Renderer;

int main(int argc, char ** argv)
{
	{
		std::shared_ptr<Application> app = ApplicationFactory::FromFile(std::string("assets/application.xml"));

		app->Start();
	}

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}