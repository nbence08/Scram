#pragma once
#include <memory>

#include "ShaderProgram.hpp"
#include "Pass.hpp"
#include "linear_algebra.hpp"

class PassBuilder {
public:
	static std::shared_ptr<Pass> buildDirShadowPass();
	static std::shared_ptr<Pass> buildPointShadowPass();
	static std::shared_ptr<Pass> buildStandardPass(bool defaultFbo = true);
};
