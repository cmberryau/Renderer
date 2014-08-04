//
//  io.cpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "utility/io.hpp"

#include <fstream>

namespace Renderer
{
	const char * IO::ReadFile(const char * file_path)
	{
        char * contents = nullptr;
        
		if(file_path == nullptr)
        {
            return nullptr;
        }
        
        std::fstream file_stream(file_path, std::ios_base::in);
        
        file_stream.seekg(0, file_stream.end);
        std::streamoff length = file_stream.tellg();
        file_stream.seekg(0, file_stream.beg);
        
        contents = new char[length];
        
        file_stream.read(contents, length);
        
        // was unsuccessful?
        if(!file_stream)
        {
            return nullptr;
        }
        
        file_stream.close();

		return contents;
	}
}