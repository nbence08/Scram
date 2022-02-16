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
	auto input = texture2DInputs.find(name);
	if (input != texture2DInputs.end() && input->second == texture) {
		return;
	}

	texture2DInputs[name] = texture;
}

void Pass::addTextureOutput(std::string name, std::shared_ptr<Texture2D> texture) {
	auto output = texture2DOutputs.find(name);
	if (output != texture2DOutputs.end() && output->second == texture) {
		return;
	}

	texture2DOutputs[name] = texture;
}

void Pass::addTextureInput(std::string name, std::shared_ptr<TextureCube> texture) {
	auto input = textureCubeInputs.find(name);
	if (input != textureCubeInputs.end() && input->second == texture) {
		return;
	}

	textureCubeInputs[name] = texture;
}

void Pass::addTextureOutput(std::string name, std::shared_ptr<TextureCube> texture) {
	auto input = textureCubeOutputs.find(name);
	if (input != textureCubeOutputs.end() && input->second == texture) {
		return;
	}

	textureCubeOutputs[name] = texture;
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
