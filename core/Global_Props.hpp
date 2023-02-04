#pragma once
#include "Preprocess_Definitions.hpp"
#include <string>

namespace global {
	static int screenWidth = 800;
	static int screenHeight = 600;

	static int shadowWidth = 2000;
	static int shadowHeight = 2000;

	//add gamma uniform to shader, and the proper Pass lambdas
	static float gamma = 2.2;

	static std::string shaderNamePrefix = "shaders/";
	static real_t shadowProjEdgeSize = 400.0;
}