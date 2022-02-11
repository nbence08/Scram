#pragma once
#include <memory>

#include "core/OpenGL/ShaderProgram.h"
#include "rendering/Pass.h"
#include "core/math/linear_algebra.hpp"

class PassBuilder {
public:
	static std::shared_ptr<Pass> buildDirShadowPass();
	static std::shared_ptr<Pass> buildStandardPass(bool defaultFbo = true);
};