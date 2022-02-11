#include "PassBuilder.h"

std::shared_ptr<Pass> PassBuilder::buildDirShadowPass() {
	FboCreateInfo createInfo;
	createInfo.colorBuffer = false;
	createInfo.depthStencilBuffer = false;
	createInfo.stencilBuffer = false;
	createInfo.depthBuffer = true;
	createInfo.height = global::shadowHeight;
	createInfo.width = global::shadowWidth;

	std::string shaderName = "dirShadow";

	auto pass = std::make_shared<Pass>(shaderName, createInfo);

	pass->prepareEntity = [pass = pass.get(), &up = pass->getProgram()->getUniformProvider()](Entity& entity) {
		up.setUniform("model", entity.model());
	};

	pass->prepareScene = [pass = pass.get()](Scene& scene) {

		auto& up = pass->getProgram()->getUniformProvider();
		auto& dirLights = scene.getDirLights();
		for (size_t i = 0; i < dirLights.size(); i++) {
			auto& dirLight = dirLights[i];
			if (dirLight.shadowMap.get() != nullptr) {
				up.setLight(dirLight, i);

				pass->addTextureOutput("dirLightShadow[" + i + ']', dirLight.shadowMap);
			}
		}
	};

	auto passScene = [pass = pass.get()](Scene& scene){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto program = pass->getProgram();
		auto& up = pass->getProgram()->getUniformProvider();
		for (int i = 0; i < scene.getDirLights().size(); i++) {
			auto dirLight = scene.getDirLights()[i];
			if (dirLight.shadowMap.get() != nullptr) {
				auto fbo = pass->getFbo();
				fbo->setDepthBuffer(dirLight.shadowMap);

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

std::shared_ptr<Pass> PassBuilder::buildStandardPass(bool defaultFbo = true) {

	std::string shaderName = "incremental";

	std::shared_ptr<Pass> pass;
	if (defaultFbo) {
		auto defaultFbo = std::make_shared<Framebuffer>(Framebuffer::getDefault());
		pass = std::make_shared<Pass>(shaderName, defaultFbo);
	}
	else {
		FboCreateInfo createInfo;
		createInfo.colorBuffer = true;
		createInfo.depthStencilBuffer = true;
		createInfo.stencilBuffer = false;
		createInfo.depthBuffer = false;
		createInfo.height = global::screenHeight;
		createInfo.width = global::screenWidth;
		pass = std::make_shared<Pass>(shaderName, createInfo);
	}

	pass->prepareScene = [pass = pass.get(), &up = pass->getProgram()->getUniformProvider()](Scene& scene) {

		auto& dirLights = scene.getDirLights();
		for (size_t i = 0; i < dirLights.size(); i++) {
			auto& dirLight = dirLights[i];
			up.setLight(dirLight, i);
			pass->addTextureInput("dirLightShadow[" + i + ']', dirLight.shadowMap);
		}

		auto& pointLights = scene.getPointLights();
		for (size_t i = 0; i < pointLights.size(); i++) {
			auto& pointLight = pointLights[i];
			up.setLight(pointLight, i);
			//pass->addTextureInput("pointLightShadow[" + i + ']', pointLight.shadowMap);
		}

		/*auto& spotLights = scene.getSpotLights();
		for (size_t i = 0; i < spotLights.size(); i++) {
			auto& spotLight = spotLights[i];
			up.setLight(spotLight, i);
			//pass->addTextureInput("pointLightShadow[" + i + ']', pointLight.shadowMap);
		}*/

		auto& camera = scene.getCamera();
		up.setUniform("view", camera.view());
		up.setUniform("projection", camera.projection());
		up.setUniform("cameraPos", Vector3(camera.getPosition()));
	};

	pass->prepareEntity = [pass = pass.get(), &up = pass->getProgram()->getUniformProvider()](Entity& entity) {
		if (entity.hasComponent<Material>()) {
			auto material = entity.getComponent<Material>();
			up.setMaterial(material, 0);
		}
		up.setUniform("model", entity.model());
	};
	return pass;
}