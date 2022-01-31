#pragma once
#include "GL/glew.h"

#pragma once
#ifdef USE_DOUBLE
using real_t = double;
#define GL_REAL GL_DOUBLE
#elif USE_FLOAT
using real_t = float;
#define GL_REAL GL_FLOAT
#endif

constexpr auto PI = 3.141592653589793238;