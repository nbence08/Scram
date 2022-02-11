#include "IncRenderer.h"

IncRenderer::IncRenderer(std::string defaultShaderPath) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	/*std::string frag = IO::readFile(defaultShaderPath + ".frag");
	std::string vert = IO::readFile(defaultShaderPath + ".vert");

	const char* fragPtr = frag.data();
	const char* vertPtr = vert.data();

	processProgram.addVertex(&vertPtr);
	processProgram.addFragment(&fragPtr);

	processProgram.linkProgram();
	processProgram.use();

	processUniforms = &processProgram.getUniformProvider();


	// to be moved away from here
	std::string prepVert = IO::readFile("shaders/dirShadow.vert");
	std::string prepFrag = IO::readFile("shaders/dirShadow.frag");

	const char* prepVertPtr = prepVert.c_str();
	const char* prepFragPtr = prepFrag.c_str();

	shadowProgram.addVertex(&prepVertPtr);
	shadowProgram.addFragment(&prepFragPtr);

	shadowProgram.linkProgram();
	shadowProgram.use();

	shadowUniforms = &shadowProgram.getUniformProvider();*/


	//experimental
	/*std::string quadVert = IO::readFile("shaders/quad.vert");
	std::string quadFrag = IO::readFile("shaders/quad.frag");

	const char* quadVertP = quadVert.c_str();
	const char* quadFragP = quadFrag.c_str();

	quadProgram.addVertex(&quadVertP);
	quadProgram.addFragment(&quadFragP);

	quadProgram.linkProgram();
	quadProgram.use();

	quadUniforms = &quadProgram.getUniformProvider();*/
	addDefaultShaders();
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

void IncRenderer::shadowRenderEntity(std::shared_ptr<Entity> entity) {
	if(entity->hasComponent<Mesh>()){
		auto& mesh = entity->getComponent<Mesh>();
		auto& vao = mesh.getVao();
		vao.bind();

		shadowUniforms->setUniform("model", entity->model());

		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

		vao.unbind();
	}
	for (auto subEntity : entity->getChildren()) {
		shadowRenderEntity(subEntity);
	}
}

void IncRenderer::renderEntity(std::shared_ptr<Entity> entity, PerspectiveCamera& camera) {
	if (entity->hasComponent<Mesh>()) {

		auto& mesh = entity->getComponent<Mesh>();
		auto& vao = mesh.getVao();
		vao.bind();

		setEntityUniforms(entity);
		processUniforms->setUniform("view", camera.view());
		processUniforms->setUniform("projection", camera.projection());
		processUniforms->setUniform("cameraPos", Vector3(camera.getPosition()));

		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

		vao.unbind();
	}
	for (auto subEntity : entity->getChildren()) {
		renderEntity(subEntity, camera);
	}
}

void IncRenderer::setEntityUniforms(std::shared_ptr<Entity> entity) {
	
	setProcessMeshModelMatrix(entity);

	setEntityMaterial(entity);
}

void IncRenderer::setProcessMeshModelMatrix(std::shared_ptr<Entity> entity) {
	Matrix4 modelWorld = entity->model();

	processUniforms->setUniform("model", modelWorld);
}

void IncRenderer::setEntityMaterial(std::shared_ptr<Entity> entity) {
	const auto& material = entity->getComponent<Material>();

	processUniforms->setMaterial(material, 0);
}

/*void IncRenderer::loadMeshVertices(Mesh& mesh) {

	vbos.emplace(mesh.uid, std::make_shared<Buffer>());
	auto& vbo = *vbos.at(mesh.uid);
	vao.bindArrayBuffer(vbo);

	auto& vertices = mesh.getVertices();
	vbo.bufferData(&vertices.data()[0], vertices.size() * sizeof(Vertex));
	vao.attributeFormat();
}

void IncRenderer::loadMeshIndices(Mesh& mesh) {

	ebos.emplace(mesh.uid, std::make_shared<Buffer>());
	auto& ebo = *ebos.at(mesh.uid);
	vao.bindIndexBuffer(ebo);

	auto& indices = mesh.getIndices();
	ebo.bufferData(&indices.data()[0], indices.size() * sizeof(unsigned int));

}*/
