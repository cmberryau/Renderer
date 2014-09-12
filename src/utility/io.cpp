//
//  io.cpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "utility/io.hpp"

#include <sstream>
#include <fstream>
#include <memory>
#include <exception>
#include <algorithm>

namespace Renderer
{
	const long long IO::kMaxFileReadBlockSize = 2048;

    std::string IO::ReadFile(std::string & file_path)
	{
        std::ifstream file_stream(file_path, std::ios_base::in);

		std::stringstream content;
		content << file_stream.rdbuf();

		return content.str();
	}
}