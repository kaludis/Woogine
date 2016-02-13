#pragma once

#include <string>
#include <vector>

namespace utils
{

namespace strings
{
    using StringList = std::vector<std::string>;
	
    StringList split(const std::string& srcstr, const char* delim);
}

}
