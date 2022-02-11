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

	void setEntityUniforms(std::shared_ptr<Entity> model);

	void setProcessMeshModelMatrix(std::shared_ptr<Entity> model);

	void setEntityMaterial(std::shared_ptr<Entity> entity);

	void addDefaultShaders();
	void addPreProcessPass(Pass&& pass) {
		preProcess.emplace_back(std::make_shared<Pass>(pass));
	}

	void addProcessPass(Pass&& pass) {
		process = std::make_shared<Pass>(pass);
	}

	void addPostProcessPass(Pass&& pass) {
		postProcess.emplace_back(std::make_shared<Pass>(pass));
	}

	ShaderProgram processProgram;
	UniformProvider* processUniforms;

	UniformProvider* shadowUniforms;
	Framebuffer shadowBuffer;
	ShaderProgram shadowProgram;

	ShaderProgram quadProgram;
	UniformProvider* quadUniforms;

public:
	IncRenderer(std::string defaultShaderName = "shaders/incremental");

	void setCullFace(bool cullFace);

	void draw(Scene& scene);
	void shadowRenderEntity(std::shared_ptr<Entity> entity);
	void renderEntity(std::shared_ptr<Entity> entity, PerspectiveCamera& camera);
};

