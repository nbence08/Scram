#include "IncRenderer.h"

IncRenderer::IncRenderer(std::string defaultShaderPath) {

	/*vao.bindArrayBuffer(vbo);
	vbo.bufferData(&cube, sizeof(cube));*/

	std::string frag = IO::readFile(defaultShaderPath + ".frag");
	std::string vert = IO::readFile(defaultShaderPath + ".vert");

	const char* fragPtr = frag.data();
	const char* vertPtr = vert.data();

	processProgram.addVertex(&vertPtr);
	processProgram.addFragment(&fragPtr);

	processProgram.linkProgram();
	processProgram.use();

	processUniforms = &processProgram.getUniformProvider();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



	// to be moved away from here
	std::string prepVert = IO::readFile("shaders/preProcess.vert");
	std::string prepFrag = IO::readFile("shaders/preProcess.frag");

	const char* prepVertPtr = prepVert.c_str();
	const char* prepFragPtr = prepFrag.c_str();

	shadowProgram.addVertex(&prepVertPtr);
	shadowProgram.addFragment(&prepFragPtr);

	shadowProgram.linkProgram();
	shadowProgram.use();

	shadowUniforms = &shadowProgram.getUniformProvider();


	//experimental
	std::string quadVert = IO::readFile("shaders/quad.vert");
	std::string quadFrag = IO::readFile("shaders/quad.frag");

	const char* quadVertP = quadVert.c_str();
	const char* quadFragP = quadFrag.c_str();

	quadProgram.addVertex(&quadVertP);
	quadProgram.addFragment(&quadFragP);

	quadProgram.linkProgram();
	quadProgram.use();

	quadUniforms = &quadProgram.getUniformProvider();
	
}

void IncRenderer::setCullFace(bool cullFace) {
	if (cullFace) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else glDisable(GL_CULL_FACE);
}

//shadow mapping implementation here is very untidy, it will be moved away, into a different architecture
// in the future
void IncRenderer::draw(Scene& scene) {


	auto& objects = scene.getObjects();
	auto& camera = scene.getCamera();

	shadowProgram.use();

	auto& dirLights = scene.getDirLights();
	auto& spotLights = scene.getSpotLights();
	auto& pointLights = scene.getPointLights();


	auto& dirLight = dirLights[0];
	
	for (auto& dirLight : dirLights) {
		if (!dirLight.shadowMap->isBoundToTextureUnit()) {
			Texture2D::bindToNewTextureUnit(dirLight.shadowMap);
		}

		shadowUniforms->setLight(dirLight, 0);

		shadowBuffer.setDepthBuffer(dirLight.shadowMap);
		shadowBuffer.bind();

		glViewport(0, 0, 800, 600);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (std::shared_ptr<Model> model : objects) {
			for (std::shared_ptr<Mesh> mesh : model->getMeshes()) {

				mesh->getVao().bind();

				//setMeshModelMatrix(mesh, model);

				Matrix4 modelWorld = model->model;
				Matrix4 meshWorld = modelWorld * mesh->getModel();

				shadowUniforms->setUniform("model", meshWorld);

				glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);

				mesh->getVao().unbind();
			}
		}
	}

	shadowBuffer.unbind();

	// experimental, draws the shadow map onto the screen, but the lower part of the draw call
	// has to be disabled in order for it to work
	/*
	quadProgram.use();

	float quadData[] = {  -1.0, 1.0, -1.0, 
						  -1.0,-1.0, -1.0,
						   1.0,-1.0, -1.0,
						   1.0,-1.0, -1.0,
						   1.0, 1.0, -1.0,
						  -1.0, 1.0, -1.0
						};

	VertexArray vao;

	vao.bind();
	vao.addReal(3);
	Buffer vbo;
	vao.bindArrayBuffer(vbo);

	vao.attributePointer();

	vbo.bufferData(&quadData, 18*sizeof(float));

	auto depthBuffer = shadowBuffer.getDepthBuffer();

	depthBuffer->getTextureUnit()->bindTexture(depthBuffer);

	quadUniforms->setUniform("quad", depthBuffer->getTextureUnitNum());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.unbind();
	*/
	
	auto depthBuffer = shadowBuffer.getDepthBuffer();
	depthBuffer->getTextureUnit()->bindTexture(depthBuffer);

	processProgram.use();
	for (const auto& dirLight : dirLights) {
		processUniforms->setLight(dirLight, 0);
	}
	for (const auto& pointLight: pointLights) {
		processUniforms->setLight(pointLight, 0);
	}

	//for (const auto& spotLight: spotLights) {
	//	uProv->setLight(spotLight, 0);
	//}

	for (std::shared_ptr<Model> model : objects) {
		for (std::shared_ptr<Mesh> mesh : model->getMeshes()) {

			mesh->getVao().bind();

			setMeshUniforms(mesh, model);
			processUniforms->setUniform("view", camera.view());
			processUniforms->setUniform("projection", camera.perspective());
			processUniforms->setUniform("cameraPos", Vector3(camera.getPosition()));

			glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
			

			//TODO
			//A different type of mesh, and IO model read function could be added, which handles the vertices, and indices of the meshes
			//as one big data structure, this way, the Model class would be the one containing all the vertices and indices
			//this could make rendering faster, where there is only one mesh, or the meshes contain few vertices

		}
	}
}

void IncRenderer::setMeshUniforms(std::shared_ptr<Mesh> mesh, std::shared_ptr<Model> model) {
	
	setMeshModelMatrix(mesh, model);

	setMeshMaterial(mesh);
}

void IncRenderer::setMeshModelMatrix(std::shared_ptr<Mesh> mesh, std::shared_ptr<Model> model) {
	Matrix4 modelWorld = model->model;
	Matrix4 meshWorld = modelWorld * mesh->getModel();

	processUniforms->setUniform("model", meshWorld);
}

void IncRenderer::setMeshMaterial(std::shared_ptr<Mesh> mesh) {
	const auto& material = mesh->getMaterial();

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
