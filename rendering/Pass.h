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

	Pass():programUniforms(nullptr), object(nullptr) {
		passMeshLambda = [](Mesh& mesh){
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
		};

		passEntityLambda = [this](Entity& entity) {
			if (entity.hasComponent<Mesh>()) {
				passMesh(entity.getComponent<Mesh>());
			}
		};

		passSceneLambda = [this](Scene& scene) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (auto entity : scene.getObjects()) {
				prepareEntity(*entity);
				passEntity(*entity);
			}
		};

		onDestroy = [](){};
	}

	Pass(std::string& shaderName, FboCreateInfo& fboInfo):Pass() {
		makeShaderProgram(shaderName);
		makeFramebuffer(fboInfo);
	}

	Pass(std::string& shaderName, std::shared_ptr<Framebuffer> fbo) :Pass() {
		makeShaderProgram(shaderName);
		this->fbo = fbo;
	}

	~Pass() {
		onDestroy();
	}

	void makeShaderProgram(std::string& shaderName) {
		this->program = std::make_shared<ShaderProgram>();
		std::string frag = IO::readFile(global::shaderNamePrefix+shaderName + ".frag");
		std::string vert = IO::readFile(global::shaderNamePrefix + shaderName + ".vert");

		const char* fragPtr = frag.data();
		const char* vertPtr = vert.data();

		program->addVertex(&vertPtr);
		program->addFragment(&fragPtr);


		std::string geom = IO::readFile(global::shaderNamePrefix + shaderName + ".geom");

		if (geom.size() > 0) {
			const char* geomPtr = geom.data();

			program->addGeometry(&geomPtr);
		}

		program->linkProgram();
	}

	void makeFramebuffer(FboCreateInfo& fboInfo) {
		this->fbo = std::make_shared<Framebuffer>(fboInfo);
	}

	void addTextureInput(std::string name, std::shared_ptr<Texture2D> texture) {
		auto input = inputs.find(name);
		if (input != inputs.end() && input->second == texture) {
			return;
		}

		outputs[name] = texture;
	}

	void addTextureOutput(std::string name, std::shared_ptr<Texture2D> texture) {
		auto output = outputs.find(name);
		if (output != outputs.end() && output->second == texture) {
			return;
		}
		
		outputs[name] = texture;
	}
	
	std::shared_ptr<ShaderProgram> getProgram() { return program; }
	std::shared_ptr<Framebuffer> getFbo() { return fbo; }
	void setFbo(std::shared_ptr<Framebuffer> fbo){ this->fbo = fbo; }
	void setProgram(std::shared_ptr<ShaderProgram> program) { this->program = program; }

	auto& getInputs() { return inputs; }
	auto& getOutputs() { return outputs; }

	void setPassMesh(std::function<void(Mesh&)> lambda) {
		this->passMeshLambda = lambda;
	}

	void setPassEntity(std::function<void(Entity&)> lambda) {
		this->passEntityLambda = lambda;
	}

	void setPassScene(std::function<void(Scene&)> lambda) {
		this->passSceneLambda = lambda;
	}
	
	void passMesh(Mesh& mesh) {
		auto& vao = mesh.getVao();
		vao.bind();

		passMeshLambda(mesh);
		/*default passMeshLambda:
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);*/

		vao.unbind();
	}

	void passEntity(Entity& entity) {
		prepareEntity(entity);
		passEntityLambda(entity);
		/*default passEntityLambda:
		if (entity.hasComponent<Mesh>()) {
			passMesh(entity.getComponent<Mesh>());
		}*/
		for (auto subEntity : entity.getChildren()) {
			passEntity(*subEntity);
		}
	}

	void passScene(Scene& scene) {
		fbo->bind();
		program->use();
		prepareScene(scene);

		passSceneLambda(scene);
		/*default passSceneLambda:
		for (auto entity : scene.getObjects()) {
			passEntity(*entity);
		}*/

		fbo->unbind();
	}
};

