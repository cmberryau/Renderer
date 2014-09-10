//
//  io.hpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include <string>

namespace Renderer
{
	class IO
	{
		public:
            static std::string ReadFile(std::string & file_path);

		protected:
			IO();
			~IO();

			static const long long kMaxFileReadBlockSize;
	};
}