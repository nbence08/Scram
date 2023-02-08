#include "Pass.hpp"

namespace ScRendering {
	Pass::Pass() :programUniforms(nullptr), object(nullptr) {
		passMeshLambda = [](SComponent::Mesh& mesh) {
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
		};

		passEntityLambda = [this](SComponent::Entity& entity) {
			if (entity.hasComponent<SComponent::Mesh>()) {
				passMesh(entity.getComponent<SComponent::Mesh>());
			}
		};

		passSceneLambda = [this](Scene& scene) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (auto entity : scene.getObjects()) {
				prepareEntity(*entity);
				passEntity(*entity);
			}
		};

		onDestroy = []() {};
	}

	Pass::Pass(std::string& shaderName, std::shared_ptr<ScOpenGL::Framebuffer> fbo) :Pass() {
		makeShaderProgram(shaderName);
		this->fbo = fbo;
	}

	Pass::~Pass() {
		onDestroy();
	}

	void Pass::makeShaderProgram(std::string& shaderName) {
		this->program = std::make_shared<ShaderProgram>();
		std::string frag = ScIO::readFile(global::shaderNamePrefix + shaderName + ".frag");
		std::string vert = ScIO::readFile(global::shaderNamePrefix + shaderName + ".vert");

		const char* fragPtr = frag.data();
		const char* vertPtr = vert.data();

		program->addVertex(&vertPtr);
		program->addFragment(&fragPtr);


		std::string geom = ScIO::readFile(global::shaderNamePrefix + shaderName + ".geom");

		if (geom.size() > 0) {
			const char* geomPtr = geom.data();

			program->addGeometry(&geomPtr);
		}

		program->linkProgram();
	}

	void Pass::makeFramebuffer(ScOpenGL::FboCreateInfo& fboInfo) {
		this->fbo = std::make_shared<ScOpenGL::Framebuffer>(fboInfo);
	}

	void Pass::addTextureInput(std::string name, std::shared_ptr<ScOpenGL::Texture2D> texture) {
		auto input = texture2DInputs.find(name);
		if (input != texture2DInputs.end() && input->second == texture) {
			return;
		}

		texture2DInputs[name] = texture;
	}

	void Pass::addTextureOutput(std::string name, std::shared_ptr<ScOpenGL::Texture2D> texture) {
		auto output = texture2DOutputs.find(name);
		if (output != texture2DOutputs.end() && output->second == texture) {
			return;
		}

		texture2DOutputs[name] = texture;
	}

	void Pass::addTextureInput(std::string name, std::shared_ptr<ScOpenGL::TextureCube> texture) {
		auto input = textureCubeInputs.find(name);
		if (input != textureCubeInputs.end() && input->second == texture) {
			return;
		}

		textureCubeInputs[name] = texture;
	}

	void Pass::addTextureOutput(std::string name, std::shared_ptr<ScOpenGL::TextureCube> texture) {
		auto input = textureCubeOutputs.find(name);
		if (input != textureCubeOutputs.end() && input->second == texture) {
			return;
		}

		textureCubeOutputs[name] = texture;
	}

	void Pass::passMesh(SComponent::Mesh& mesh) {
		auto& vao = mesh.getVao();
		vao.bind();

		passMeshLambda(mesh);
		/*default passMeshLambda:
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);*/

		vao.unbind();
	}

	void Pass::passEntity(SComponent::Entity& entity) {
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

	void Pass::passScene(Scene& scene) {
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
}
