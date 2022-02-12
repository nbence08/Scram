#include "Pass.h"

Pass::Pass() :programUniforms(nullptr), object(nullptr) {
	passMeshLambda = [](Mesh& mesh) {
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

	onDestroy = []() {};
}

Pass::Pass(std::string& shaderName, std::shared_ptr<Framebuffer> fbo) :Pass() {
	makeShaderProgram(shaderName);
	this->fbo = fbo;
}

Pass::~Pass() {
	onDestroy();
}

void Pass::makeShaderProgram(std::string& shaderName) {
	this->program = std::make_shared<ShaderProgram>();
	std::string frag = IO::readFile(global::shaderNamePrefix + shaderName + ".frag");
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

void Pass::makeFramebuffer(FboCreateInfo& fboInfo) {
	this->fbo = std::make_shared<Framebuffer>(fboInfo);
}

void Pass::addTextureInput(std::string name, std::shared_ptr<Texture2D> texture) {
	auto input = inputs.find(name);
	if (input != inputs.end() && input->second == texture) {
		return;
	}

	outputs[name] = texture;
}

void Pass::addTextureOutput(std::string name, std::shared_ptr<Texture2D> texture) {
	auto output = outputs.find(name);
	if (output != outputs.end() && output->second == texture) {
		return;
	}

	outputs[name] = texture;
}

void Pass::passMesh(Mesh& mesh) {
	auto& vao = mesh.getVao();
	vao.bind();

	passMeshLambda(mesh);
	/*default passMeshLambda:
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);*/

	vao.unbind();
}

void Pass::passEntity(Entity& entity) {
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