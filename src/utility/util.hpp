#ifndef _renderer_util_hpp
#define _renderer_util_hpp

#include <string>
#include <vector>
#include <sstream>

namespace Renderer
{
    std::vector<std::string> & split_string(const std::string &string,
                                            char delim,
                                            std::vector<std::string> &lines);
    
    std::vector<std::string> split_string(const std::string &string,
                                          char delim);
}

#endif // _renderer_util_hpp