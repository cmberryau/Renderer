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
#ifdef _WIN32
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

	auto debug_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	debug_flags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(debug_flags);
#endif

	{
		auto app = ApplicationFactory::FromFile(std::string("assets/application.xml"));
		app->Start();
	}

	return 0;
}