#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "GL/glew.h"
#include "core/OpenGL/VertexArray.hpp"
#include "core/OpenGL/Buffer.hpp"
#include "core/OpenGL/ShaderProgram.hpp"
#include "core/OpenGL/Framebuffer.hpp"
#include "core/CubeData.hpp"
#include "core/Global_Props.hpp"
#include "core/math/linear_algebra.hpp"

#include "io/IO.hpp"

#include "components/PerspectiveCamera.hpp"
#include "components/Transform.hpp"

#include "Scene.hpp"
#include "Pass.hpp"
#include "PassBuilder.hpp"

namespace ScRendering {
	//incremental renderer
	class IncRenderer {

		std::vector<std::shared_ptr<Pass>> preProcess;
		std::shared_ptr<Pass> process;
		std::vector<std::shared_ptr<Pass>> postProcess;

		void addDefaultPasses();
		inline void addPreProcessPass(Pass&& pass) {
			preProcess.emplace_back(std::make_shared<Pass>(pass));
		}

		inline void addProcessPass(Pass&& pass) {
			process = std::make_shared<Pass>(pass);
		}

		inline void addPostProcessPass(Pass&& pass) {
			postProcess.emplace_back(std::make_shared<Pass>(pass));
		}

	public:
		IncRenderer(std::string defaultShaderName = "shaders/incremental");
		void setCullFace(bool cullFace);
		void draw(Scene& scene);
	};
}
