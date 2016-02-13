#include "stringutl.h"

namespace utils
{
    namespace strings
    {
	StringList split(const std::string& srcstr, const char* delim)
	{
	    StringList vec;
    
	    std::string str = srcstr;
	    std::string::size_type start_pos{0};
	    std::string::size_type end_pos{0};

	    do {
		end_pos = str.find(delim, start_pos);
		vec.push_back(str.substr(start_pos, end_pos - start_pos));
		start_pos = end_pos + 1;
	    } while (end_pos != std::string::npos);

	    return vec;	    
	}
    }
}
