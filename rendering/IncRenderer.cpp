#include "IncRenderer.hpp"

namespace ScRendering {
	IncRenderer::IncRenderer(std::string defaultShaderPath) {

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		glClearDepth(1.0);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		addDefaultPasses();
	}

	void IncRenderer::addDefaultPasses() {
		preProcess.push_back(PassBuilder::buildDirShadowPass());
		preProcess.push_back(PassBuilder::buildPointShadowPass());

		process = PassBuilder::buildStandardPass();
	}

	void IncRenderer::setCullFace(bool cullFace) {
		if (cullFace) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else glDisable(GL_CULL_FACE);
	}

	void IncRenderer::draw(Scene& scene) {
		auto& dirLights = scene.getDirLights();
		auto& spotLights = scene.getSpotLights();
		auto& pointLights = scene.getPointLights();

		for (size_t i = 0; i < preProcess.size(); i++) {
			auto curPreProcess = preProcess[i];

			curPreProcess->passScene(scene);
		}

		process->passScene(scene);

		for (size_t i = 0; i < postProcess.size(); i++) {
			auto curPostProcess = postProcess[i];

			curPostProcess->passScene(scene);
		}
	}
}
