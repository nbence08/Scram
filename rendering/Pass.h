#pragma once
#include <functional>
#include "core/OpenGL/ShaderProgram.h"
#include "core/OpenGL/Framebuffer.h"
#include "main/Logger.h"
#include "rendering/Scene.h"
#include "io/io.h"

enum class PassType {
	preProcess,
	process,
	postProcess
};

class Pass {
	std::string shaderName;

	std::shared_ptr<ShaderProgram> program;
	UniformProvider* programUniforms;
	std::shared_ptr<Framebuffer> fbo;

	std::unordered_map<std::string, std::shared_ptr<Texture2D>> inputs;
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> outputs;


	std::function<void(Mesh&)> passMeshLambda;
	std::function<void(Entity&)> passEntityLambda;
	std::function<void(Scene&)> passSceneLambda;

public:
	std::function<void(Scene&)> prepareScene;
	std::function<void(Entity&)> prepareEntity;

	void* object;
	std::function<void()> onDestroy;

	Pass();

	inline Pass(std::string& shaderName, FboCreateInfo& fboInfo):Pass() {
		makeShaderProgram(shaderName);
		makeFramebuffer(fboInfo);
	}

	Pass(std::string& shaderName, std::shared_ptr<Framebuffer> fbo);

	~Pass();

	void makeShaderProgram(std::string& shaderName);

	void makeFramebuffer(FboCreateInfo& fboInfo);

	void addTextureInput(std::string name, std::shared_ptr<Texture2D> texture);

	void addTextureOutput(std::string name, std::shared_ptr<Texture2D> texture);
	
	inline std::shared_ptr<ShaderProgram> getProgram() { return program; }
	inline std::shared_ptr<Framebuffer> getFbo() { return fbo; }
	inline void setFbo(std::shared_ptr<Framebuffer> fbo){ this->fbo = fbo; }
	inline void setProgram(std::shared_ptr<ShaderProgram> program) { this->program = program; }

	inline auto& getInputs() { return inputs; }
	inline auto& getOutputs() { return outputs; }

	inline void setPassMesh(std::function<void(Mesh&)> lambda) {
		this->passMeshLambda = lambda;
	}

	inline void setPassEntity(std::function<void(Entity&)> lambda) {
		this->passEntityLambda = lambda;
	}

	inline void setPassScene(std::function<void(Scene&)> lambda) {
		this->passSceneLambda = lambda;
	}
	
	void passMesh(Mesh& mesh);

	void passEntity(Entity& entity);

	void passScene(Scene& scene);
};

