#include "Pass.hpp"
#include "Material.hpp"

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

	Pass::Pass(const ShaderSources& sources, std::shared_ptr<ScOpenGL::Framebuffer> fbo) :Pass() {
		makeShaderProgram(sources);
		this->fbo = fbo;
	}

	Pass::~Pass() {
		onDestroy();
	}

	void Pass::makeShaderProgram(const ShaderSources& sources) {
		this->program = std::make_shared<ScOpenGL::ShaderProgram>();
		const std::string& frag = sources.fragment;
		const std::string& vert = sources.vertex;

		const char* fragPtr = frag.data();
		const char* vertPtr = vert.data();

		program->addVertex(&vertPtr);
		program->addFragment(&fragPtr);

		const std::string& geom = sources.geometry;
		if (sources.geometry.size() != 0) {
		}

		if (!geom.empty()) {
			const char* geomPtr = geom.data();

			program->addGeometry(&geomPtr);
		}

		program->linkProgram();
	}

	void Pass::makeFramebuffer(ScOpenGL::FboCreateInfo& fboInfo) {
		this->fbo = std::make_shared<ScOpenGL::Framebuffer>(fboInfo);
	}

	void Pass::addTextureInput(const std::string& name, std::shared_ptr<ScOpenGL::Texture2D> texture) {
		auto input = texture2DInputs.find(name);
		if (input != texture2DInputs.end() && input->second == texture) {
			return;
		}

		texture2DInputs[name] = texture;
	}

	void Pass::addTextureOutput(const std::string& name, std::shared_ptr<ScOpenGL::Texture2D> texture) {
		auto output = texture2DOutputs.find(name);
		if (output != texture2DOutputs.end() && output->second == texture) {
			return;
		}

		texture2DOutputs[name] = texture;
	}

	void Pass::addTextureInput(const std::string& name, std::shared_ptr<ScOpenGL::TextureCube> texture) {
		auto input = textureCubeInputs.find(name);
		if (input != textureCubeInputs.end() && input->second == texture) {
			return;
		}

		textureCubeInputs[name] = texture;
	}

	void Pass::addTextureOutput(const std::string& name, std::shared_ptr<ScOpenGL::TextureCube> texture) {
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

	void Pass::setLight(const SComponent::PointLight& light, int index, std::string arrayName) {
		program->setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
		program->setUniform(arrayName + "[" + std::to_string(index) + "].attenuation", light.attenuation);
		program->setUniform(arrayName + "[" + std::to_string(index) + "].position", light.position);
		if (light.hasShadowMap()) {
			program->setUniform(arrayName + "ShadowMap[" + std::to_string(index) + "]", light.shadowMap->getTextureUnitNum());
			auto lightSpaceMatrices = light.getLightSpaceMatrices();
			program->setUniform(arrayName + "[" + std::to_string(index) + "].farPlane", light.farPlane);
			for (int i = 0; i < 6; i++) {
				program->setUniform(arrayName + "[" + std::to_string(index) + "].lightMatrices[" + std::to_string(i) + "]", lightSpaceMatrices[i]);
			}
		}
	}

	void Pass::setLight(const SComponent::DirectionalLight& light, int index, std::string arrayName) {
		program->setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
		program->setUniform(arrayName + "[" + std::to_string(index) + "].direction", light.direction.normalized());
		program->setUniform(arrayName + "[" + std::to_string(index) + "].lightMatrix", light.getLightSpaceMatrix());
		if (light.hasShadowMap()) {
			program->setUniform(arrayName + "[" + std::to_string(index) + "].shadowMap", light.shadowMap->getTextureUnitNum());
		}
	}

	//TODO: add setLight for SpotLights

	void Pass::setMaterial(const SComponent::Material& material, int index, std::string arrayName) {
		bool albedo_is_texture;
		if (material.albedo.index() == 0) { //Vector3

			ScMath::Vector3 albedo = std::get<ScMath::Vector3>(material.albedo);
			albedo_is_texture = false;

			program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
			program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
		}
		else { //Texture

			ScOpenGL::Texture2D& albedo = *std::get<std::shared_ptr<ScOpenGL::Texture2D>>(material.albedo);
			auto textureUnit = albedo.getTextureUnitNum();
			if (textureUnit == -1) {
				//TODO: automatic texture unit creation could be implemented in the future
				ScMath::Vector3 albedo(1.0, 0.0, 1.0);
				albedo_is_texture = false;

				program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
				program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
			}
			albedo_is_texture = true;
			program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", ScMath::Vector3(0.0, 0.0, 0.0));
			program->setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", textureUnit);
		}

		program->setUniform(arrayName + "[" + std::to_string(index) + "].albedo_is_texture", albedo_is_texture);
		program->setUniform(arrayName + "[" + std::to_string(index) + "].smoothness", material.smoothness);
		program->setUniform(arrayName + "[" + std::to_string(index) + "].metalness", material.metalness);

		if (material.hasEmission()) {
			if (material.hasEmissionTexture()) {
				const auto tex = std::get<std::shared_ptr<ScOpenGL::Texture2D>>(material.emission);
				program->setUniform(arrayName + "[" + std::to_string(index) + "].has_emission", true);
				program->setUniform(arrayName + "[" + std::to_string(index) + "].emissionTexture", tex->getTextureUnitNum());
			}
			else if (material.hasEmissionVector()) {
				//ISSUE: constant emission vector is not supported, to be mended
				program->setUniform(arrayName + "[" + std::to_string(index) + "].has_emission", false);
			}
		}
	}
}
