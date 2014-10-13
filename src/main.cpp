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

void entry()
{
	std::shared_ptr<Application> app = ApplicationFactory::FromFile(std::string("sup"));

	app->Start();
}

int main(int argc, char ** argv)
{
	entry();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}