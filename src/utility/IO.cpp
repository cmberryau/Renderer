//
//  io.cpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "utility/IO.hpp"

#include <sstream>
#include <fstream>

namespace Renderer
{
	std::string IO::ReadFile(const std::string & file_path)
	{
        std::ifstream file_stream(file_path, std::ios_base::in);

        if(!file_stream.good())
        {
            std::string error_msg("File ");
            error_msg += file_path;
            error_msg += " could not be found or accessed.";

            throw std::runtime_error(error_msg);
        }
        
		std::stringstream content;
		content << file_stream.rdbuf();

		return content.str();
	}
}