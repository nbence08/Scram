#pragma once
#include "Preprocess_Definitions.h"
#include <string>

namespace global {
	static int screenWidth = 800;
	static int screenHeight = 600;

	static int shadowWidth = 1600;
	static int shadowHeight = 1200;

	static std::string shaderNamePrefix = "shaders/";
	static real_t shadowProjEdgeSize = 400.0;
}