#include "IncRenderer.h"

IncRenderer::IncRenderer(std::string defaultShaderPath) {

	/*vao.bindArrayBuffer(vbo);
	vbo.bufferData(&cube, sizeof(cube));*/

	std::string frag = IO::readFile(defaultShaderPath + ".frag");
	std::string vert = IO::readFile(defaultShaderPath + ".vert");

	const char* fragPtr = frag.data();
	const char* vertPtr = vert.data();

	program.addVertex(&vertPtr);
	program.addFragment(&fragPtr);

	program.linkProgram();
	program.use();

	uProv = &program.getUniformProvider();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	FboCreateInfo shadowInfo;
	shadowInfo.depthBuffer = true;
	
	shadowBuffer.createDepthBuffer(global::screenWidth, global::screenHeight);
}

void IncRenderer::setCullFace(bool cullFace) {
	if (cullFace) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
}

void IncRenderer::draw(Scene& scene) {


	auto& objects = scene.getObjects();
	auto& camera = scene.getCamera();

	program.use();

	auto& dirLights = scene.getDirLights();
	auto& spotLights = scene.getSpotLights();
	auto& pointLights = scene.getPointLights();

	for (const auto& dirLight : dirLights) {
		uProv->setLight(dirLight, 0);
	}
	for (const auto& pointLight: pointLights) {
		uProv->setLight(pointLight, 0);
	}

	/*for (const auto& spotLight: spotLights) {
		uProv->setLight(spotLight, 0);
	}*/

	for (std::shared_ptr<Model> model : objects) {
		for (std::shared_ptr<Mesh> mesh : model->getMeshes()) {

			mesh->getVao().bind();

			setMeshUniforms(mesh, model);
			uProv->setUniform("view", camera.view());
			uProv->setUniform("projection", camera.perspective());
			uProv->setUniform("cameraPos", Vector3(camera.getPosition()));

			glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
			

			//TODO
			//A different type of mesh, and IO model read function could be added, which handles the vertices, and indices of the meshes
			//as one big data structure, this way, the Model class would be the one containing all the vertices and indices
			//this could make rendering faster, where there is only one mesh, or the meshes contain few vertices

		}
	}
}

void IncRenderer::setMeshUniforms(std::shared_ptr<Mesh> mesh, std::shared_ptr<Model> model) {
	Matrix4 modelWorld = model->model;
	Matrix4 meshWorld = modelWorld * mesh->getModel();

	uProv->setUniform("model", meshWorld);
	const auto& material = mesh->getMaterial();

	uProv->setMaterial(material, 0);
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
