//
//  io.cpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "utility/io.hpp"

#include <fstream>
#include <exception>
#include <algorithm>
#include <string>
#include <memory>

namespace Renderer
{
	const long long IO::kMaxFileReadBlockSize = 2048;

    char * IO::ReadFile(const char * file_path)
	{		
		char * contents = nullptr;
		std::unique_ptr<char> contents_unique(contents);
        
		if(file_path == nullptr)
        {
            return nullptr;
        }
        
		// create a filestream, find the size of the file
        std::fstream file_stream(file_path, std::ios_base::in);
        file_stream.seekg(0, file_stream.end);
        std::streamoff length = file_stream.tellg();        
		file_stream.seekg(0, file_stream.beg);

		// create the buffer for it to go into
        contents = new char[length + 1];
		std::streamoff remaining = length;
		while (remaining > 0)
		{
			std::streamoff buffer_size = std::min(remaining, kMaxFileReadBlockSize);
			file_stream.read(contents + (length - remaining), buffer_size);

			remaining -= kMaxFileReadBlockSize;
		}        
        
		// check for errors in the stream
		if (!file_stream)
		{
			if (!file_stream.eof())
			{
				throw std::exception();
			}
		}
        
        file_stream.close();

        // cap the end of the char array
        contents[length] = NULL;
		contents_unique.release();

		return contents;
	}
}