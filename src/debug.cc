#include "debug.h"

#include <GL/glew.h>

#include <cstdlib>

namespace utils
{
    namespace debug
    {
	void check_error(const char* file, int line, const char* func)
	{
	    GLenum ret = glGetError();

	    if (ret != GL_NO_ERROR) {
		std::fprintf(stderr, "ERROR %s:%d:%s(): %s\n", file, line, func,
			     gluErrorString(ret));
		exit(EXIT_FAILURE);
	    }
	}
    } /* namespace debug */
} /* namespace utils */
