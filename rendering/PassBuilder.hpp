#pragma once

#include "rendering_export.hpp"

#include <memory>

#include "ShaderProgram.hpp"
#include "Pass.hpp"
#include "linear_algebra.hpp"

namespace ScRendering {

	class RENDERING_EXPORT PassBuilder {
	private:
		static ShaderSources readShaders(std::string& name);
	public:
		static std::shared_ptr<Pass> buildDirShadowPass();
		static std::shared_ptr<Pass> buildPointShadowPass();
		static std::shared_ptr<Pass> buildStandardPass(bool defaultFbo = true);
	};

}
