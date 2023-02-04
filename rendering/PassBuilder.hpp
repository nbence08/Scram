#pragma once
#include <memory>

#include "core/OpenGL/ShaderProgram.hpp"
#include "rendering/Pass.hpp"
#include "core/math/linear_algebra.hpp"

class PassBuilder {
public:
	static std::shared_ptr<Pass> buildDirShadowPass();
	static std::shared_ptr<Pass> buildPointShadowPass();
	static std::shared_ptr<Pass> buildStandardPass(bool defaultFbo = true);
};
