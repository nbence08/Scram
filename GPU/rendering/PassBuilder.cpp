#include "PassBuilder.hpp"

namespace ScRendering {

	std::shared_ptr<Pass> PassBuilder::buildDirShadowPass() {
		ScOpenGL::FboCreateInfo createInfo;
		createInfo.colorBuffer = false;
		createInfo.depthStencilBuffer = false;
		createInfo.stencilBuffer = false;
		createInfo.depthBuffer = true;
		createInfo.height = global::shadowHeight;
		createInfo.width = global::shadowWidth;

		std::string shaderName = "dirShadow";

		auto pass = std::make_shared<Pass>(shaderName, createInfo);

		pass->prepareEntity = [program = pass->getProgram().get()](SComponent::Entity& entity) {
			program->setUniform("model", entity.model());
		};

		pass->prepareScene = [pass = pass.get(), program = pass->getProgram().get()](Scene& scene) {
			glViewport(0, 0, global::shadowWidth, global::shadowHeight);
			glCullFace(GL_FRONT);

			auto& dirLights = scene.getDirLights();
			for (size_t i = 0; i < dirLights.size(); i++) {
				auto& dirLight = dirLights[i];
				if (dirLight.shadowMap.get() != nullptr) {
					program->setUniform(dirLight, i);

					pass->addTextureOutput("dirLightShadow[" + i + ']', dirLight.shadowMap);

					if (!dirLight.shadowMap->isBoundToTextureUnit()) {
						ScOpenGL::Texture2D::bindToNewTextureUnit(dirLight.shadowMap);
					}
				}
			}
		};

		auto passScene = [pass = pass.get()](Scene& scene){

			auto program = pass->getProgram();
			auto& up = pass->getProgram()->getUniformProvider();
			for (int i = 0; i < scene.getDirLights().size(); i++) {
				auto dirLight = scene.getDirLights()[i];
				if (dirLight.shadowMap.get() != nullptr) {
					auto fbo = pass->getFbo();
					fbo->setDepthBuffer(dirLight.shadowMap);
					glClear(GL_DEPTH_BUFFER_BIT);

					program->setUniform("lightIndex", i);
					for (auto& entity : scene.getObjects()) {
						pass->passEntity(*entity);
					}
				}
			}
		};
		pass->setPassScene(passScene);
		return pass;
	}

	std::shared_ptr<Pass> PassBuilder::buildStandardPass(bool defaultFbo) {

		std::string shaderName = "incremental";

		std::shared_ptr<Pass> pass;
		if (defaultFbo) {
			auto defaultFbo = std::make_shared<ScOpenGL::Framebuffer>(ScOpenGL::Framebuffer::getDefault());
			pass = std::make_shared<Pass>(shaderName, defaultFbo);
		}
		else {
			ScOpenGL::FboCreateInfo createInfo;
			createInfo.colorBuffer = true;
			createInfo.depthStencilBuffer = true;
			createInfo.stencilBuffer = false;
			createInfo.depthBuffer = false;
			createInfo.height = global::screenHeight;
			createInfo.width = global::screenWidth;
			pass = std::make_shared<Pass>(shaderName, createInfo);
		}

		pass->prepareScene = [pass = pass.get(), program = pass->getProgram()](Scene& scene) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, global::screenWidth, global::screenHeight);
			glCullFace(GL_BACK);

			program->setUniform("gamma", global::gamma);
			auto& dirLights = scene.getDirLights();
			for (size_t i = 0; i < dirLights.size(); i++) {
				auto& dirLight = dirLights[i];
				program->setUniform(dirLight, i);
				pass->addTextureInput("dirLightShadow[" + std::to_string(i) + "].shadowMap", dirLight.shadowMap);
			}

			auto& pointLights = scene.getPointLights();
			for (size_t i = 0; i < pointLights.size(); i++) {
				auto& pointLight = pointLights[i];
				program->setUniform(pointLight, i);
				pass->addTextureInput("pointLights[" + std::to_string(i) + "].shadowCube", pointLight.shadowMap);
			}

			/*auto& spotLights = scene.getSpotLights();
			for (size_t i = 0; i < spotLights.size(); i++) {
				auto& spotLight = spotLights[i];
				up.setLight(spotLight, i);
				//pass->addTextureInput("spotLights[" + i + ']', pointLight.shadowMap);
			}*/

			auto& camera = scene.getCamera();
			program->setUniform("view", camera.view());
			program->setUniform("projection", camera.projection());
			program->setUniform("cameraPos", Smath::Vector3(camera.getPosition()));
		};

		pass->prepareEntity = [pass = pass.get(), program = pass->getProgram()](SComponent::Entity& entity) {
			if (entity.hasComponent<SComponent::Material>()) {
				auto material = entity.getComponent<SComponent::Material>();
				program->setUniform(material, 0);
			}
			program->setUniform("model", entity.model());
		};
		return pass;
	}

	std::shared_ptr<Pass> PassBuilder::buildPointShadowPass() {
		ScOpenGL::FboCreateInfo createInfo;
		createInfo.colorBuffer = false;
		createInfo.depthStencilBuffer = false;
		createInfo.stencilBuffer = false;
		createInfo.depthBuffer = true;
		createInfo.height = global::shadowHeight;
		createInfo.width = global::shadowWidth;

		std::string shaderName = "pointShadow";

		auto pass = std::make_shared<Pass>(shaderName, createInfo);

		pass->prepareEntity = [program = pass->getProgram().get()](SComponent::Entity& entity) {
			program->setUniform("model", entity.model());
		};

		pass->prepareScene = [pass = pass.get(), program = pass->getProgram().get()](Scene& scene) {
			glViewport(0, 0, global::shadowWidth, global::shadowHeight);
			glCullFace(GL_FRONT);

			auto& pointLights = scene.getPointLights();
			for (size_t i = 0; i < pointLights.size(); i++) {
				auto& pointLight = pointLights[i];
				if (pointLight.shadowMap.get() != nullptr) {
					program->setUniform(pointLight, i);
					pass->addTextureOutput("pointLightShadow[" + i + ']', pointLight.shadowMap);

					if (!pointLight.shadowMap->isBoundToTextureUnit()) {
						ScOpenGL::TextureCube::bindToNewTextureUnit(pointLight.shadowMap);
					}
				}
			}
		};

		auto passScene = [pass = pass.get()](Scene& scene){

			auto program = pass->getProgram();
			auto& up = pass->getProgram()->getUniformProvider();
			auto& pointLights = scene.getPointLights();
			for (int i = 0; i < pointLights.size(); i++) {
				auto dirLight = pointLights[i];
				if (dirLight.shadowMap.get() != nullptr) {
					auto fbo = pass->getFbo();
					fbo->setDepthBuffer(dirLight.shadowMap);
					glClear(GL_DEPTH_BUFFER_BIT);

					program->setUniform("lightIndex", i);
					for (auto& entity : scene.getObjects()) {
						pass->passEntity(*entity);
					}
				}
			}
		};
		pass->setPassScene(passScene);
		return pass;
	}
}
