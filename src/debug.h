#pragma once

#include <cstdio>

namespace utils
{
    namespace debug
    {
	void check_error(const char* file, int line, const char* func);
    } /* namespace debug */
} /* namespace utils */

#ifdef DEBUG
#define CHECK_ERR() utils::debug::check_error(__FILE__, __LINE__, __func__)
#else
#define CHECK_ERR()
#endif // DEBUG

#ifdef DEBUG
#define DEBUG_MSG(fmt, ...)	\
	do { fprintf(stdout, "%s:%d:%s(): " fmt, __FILE__, \
			__LINE__, __func__); } while (0)

#define DEBUG_PRINT(fmt, ...)	\
	do { fprintf(stdout, "%s:%d:%s(): " fmt, __FILE__, \
			__LINE__, __func__, __VA_ARGS__); } while (0)

#define DEBUG_PRINT_WARN(fmt, ...)	\
	do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
			__LINE__, __func__, __VA_ARGS__); } while (0)

#define DEBUG_PRINT_ERR(fmt, ...)	\
	do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
			__LINE__, __func__, __VA_ARGS__); } while (0)
#else
#define DEBUG_MSG(fmt, ...)	
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_PRINT_WARN(fmt, ...)
#define DEBUG_PRINT_ERR(fmt, ...)
#endif // DEBUG

#define UNUSED(arg) (void)(arg)

#define BUFFER_OFFSET(idx)	\
	(static_cast<char*>(0) + idx)
