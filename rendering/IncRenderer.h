#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "GL/glew.h"
#include "core/OpenGL/VertexArray.h"
#include "core/OpenGL/Buffer.h"
#include "core/OpenGL/ShaderProgram.h"
#include "core/OpenGL/Framebuffer.h"
#include "core/CubeData.hpp"
#include "core/Global_Props.hpp"
#include "core/math/linear_algebra.hpp"

#include "io/IO.h"

#include "components/PerspectiveCamera.h"
#include "components/Transform.h"

#include "Scene.h"
#include "Pass.h"
#include "PassBuilder.h"

//incremental renderer
class IncRenderer {

	std::vector<std::shared_ptr<Pass>> preProcess;
	std::shared_ptr<Pass> process;
	std::vector<std::shared_ptr<Pass>> postProcess;

	void addDefaultShaders();
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
