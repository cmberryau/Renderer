#include "util.hpp"

namespace Renderer
{
    // taken from http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c answered by Evan Teran
    std::vector<std::string> & split_string(const std::string &string,
                                            char delim,
                                            std::vector<std::string> &lines)
    {
        std::stringstream string_stream(string);
        std::string line;
        
        while(std::getline(string_stream, line, delim))
        {
            lines.push_back(line);
        }
        
        return lines;
    }
    
    std::vector<std::string> split_string(const std::string &string,
                                          char delim)
    {
        std::vector<std::string> lines;
        
        split_string(string, delim, lines);
        
        return lines;
    }
}