#include "IncRenderer.h"

IncRenderer::IncRenderer(std::string defaultShaderPath) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	addDefaultShaders();
	
	sBuffer = std::make_shared<Framebuffer>();
	sProgram = std::make_shared<ShaderProgram>();

	std::string shaderName = "pointShadow";
	std::string frag = IO::readFile(global::shaderNamePrefix + shaderName + ".frag");
	std::string vert = IO::readFile(global::shaderNamePrefix + shaderName + ".vert");
	std::string geom = IO::readFile(global::shaderNamePrefix + shaderName + ".geom");

	const char* fragPtr = frag.data();
	const char* vertPtr = vert.data();
	const char* geomPtr = geom.data();

	sProgram->addVertex(&vertPtr);
	sProgram->addFragment(&fragPtr);
	sProgram->addGeometry(&geomPtr);

	sProgram->linkProgram();

	sUniforms = &sProgram->getUniformProvider();
}
void IncRenderer::addDefaultShaders() {
	preProcess.push_back(PassBuilder::buildDirShadowPass());
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


	for (auto& dirLight : dirLights) {
		if (!dirLight.shadowMap->isBoundToTextureUnit()) {
			Texture2D::bindToNewTextureUnit(dirLight.shadowMap);
		}
	}
	//EXPERIMENTAL
	sProgram->use();
	glViewport(0, 0, global::shadowWidth, global::shadowWidth);

	for (auto& light : scene.getPointLights()) {
		if (!light.shadowMap->isBoundToTextureUnit()) {
			TextureCube::bindToNewTextureUnit(light.shadowMap);
		}

		sBuffer->setDepthBuffer(light.shadowMap);
		sBuffer->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		sUniforms->setLight(light, 0);
		sUniforms->setUniform("lightIndex", 0);
		sUniforms->setUniform("farPlane", 900.0f);

		for (auto& obj : scene.getObjects()) {
			drawEntity(obj);
		}
			
	}

	//EXPERIMENTAL

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

void IncRenderer::drawEntity(std::shared_ptr<Entity> obj){
	if (obj->hasComponent<Mesh>()) {
		auto& mesh = obj->getComponent<Mesh>();
		auto& vao = mesh.getVao();
		vao.bind();
		sUniforms->setUniform("model", obj->model());

		glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

	}
	for (auto c : obj->getChildren()) {
		drawEntity(c);
	}
}

