//-----------------------------------------------------------------------------
// Contain macros and stuff to use throughout the code...
//-----------------------------------------------------------------------------
#pragma once

#include <cstdio>

#ifdef _DEBUG
	#define DEBUG_PRINT(...) std::printf(__VA_ARGS__);
#else
	#define DEBUG_PRINT(...)
#endif

#define LITTLE_SHORT(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))
#define LITTLE_INT(x)	((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))
#define BIG_SHORT(x)	(x)
#define BIG_INT(x)		(x)