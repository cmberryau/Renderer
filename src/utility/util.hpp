//
//  util.hpp
//  Renderer
//
//  Created by Christopher Berry on 09/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#ifndef _util_h
#define _util_h

#include <string>
#include <vector>

namespace Renderer
{
    std::vector<std::string> & split_string(const std::string & string,
                                            char delim,
                                            std::vector<std::string> & lines);
    
    std::vector<std::string> split_string(const std::string &string,
                                          char delim);
}

#endif // _util_h