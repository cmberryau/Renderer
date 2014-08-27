//
//  io.hpp
//  Renderer
//
//  Created by Christopher Berry on 03/08/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

namespace Renderer
{
	class IO
	{
		public:
			static char * ReadFile(const char * file_path);

		protected:
			IO();
			~IO();
	};
}