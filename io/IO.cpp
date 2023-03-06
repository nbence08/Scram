#include "IO.hpp"

namespace ScIO {
	std::string readFile(const std::string& path) {
		std::ifstream in(path);

		std::string content(std::istreambuf_iterator<char>{in}, {});
		in.close();
		return content;
	}

	ImageData2D readImage(const std::string& path) {
		ImageData2D data{};

		stbi_set_flip_vertically_on_load(true);

		data.pixels = stbi_load(path.c_str(), &data.width, &data.height, &data.internalFormat, 0);
		if (!data.pixels) {
			throw std::runtime_error("Could not load image.");
		}
		if (data.internalFormat == 3) {
			data.internalFormat = GL_RGB;
			data.format = GL_RGB;
		}
		else if (data.internalFormat == 4) {
			data.internalFormat = GL_RGBA;
			data.format = GL_RGBA;
		}

		data.level = 0;
		data.type = GL_UNSIGNED_BYTE;

		return data;
	}

	void freeImage(ImageData2D& data) {
		stbi_image_free(data.pixels);
	}


	void parseMeshVertices(const aiMesh& aiMesh, SComponent::Mesh& mesh) {
		auto& vertices = mesh.getVertices();
		vertices.resize(aiMesh.mNumVertices);
		const aiVector3D* aiVertices = aiMesh.mVertices;
		const aiVector3D* aiNormals = aiMesh.mNormals;
		const aiVector3D* aiTexCoords = aiMesh.mTextureCoords[0];

		for (unsigned int i = 0; i < aiMesh.mNumVertices; i++) {
			const aiVector3D aiVertex = aiVertices[i];
			const aiVector3D aiNormal = aiNormals[i];
			const aiVector3D aiTexCoord = aiTexCoords[i];

			vertices[i].position = ScMath::Vector3(aiVertex.x, aiVertex.y, aiVertex.z);
			vertices[i].normal = ScMath::Vector3(aiNormal.x, aiNormal.y, aiNormal.z);
			vertices[i].texCoord = ScMath::Vector2(aiTexCoord.x, aiTexCoord.y);
		}

		mesh.bufferVertices();
	}

	ImageData2D create2DImageData(aiTexture& aiTex) {
		ImageData2D data;


		if (aiTex.mHeight == 0) {
			stbi_set_flip_vertically_on_load(true);
			data.pixels = stbi_load_from_memory(reinterpret_cast<stbi_uc const*>(aiTex.pcData), aiTex.mWidth, &data.width, &data.height, &data.internalFormat, 4);

			data.internalFormat = GL_RGBA;
			data.format = GL_RGBA;
			data.type = GL_UNSIGNED_BYTE;
		}
		else {
			data.format = GL_RGBA;
			data.internalFormat = GL_RGBA;
			data.height = aiTex.mHeight;
			data.width = aiTex.mWidth;
			data.type = GL_UNSIGNED_BYTE;
			data.pixels = aiTex.pcData;
		}

		return data;
	}

	std::shared_ptr<ScOpenGL::Texture2D> transferTextureToOpenGL(const aiScene& scene, std::string& strPath) {
		std::string idxStr = strPath.substr(1, std::string::npos);
		int idxInt = std::stoi(idxStr);

		aiTexture& aiTex = *scene.mTextures[idxInt];
		auto texture = std::make_shared<ScOpenGL::Texture2D>();
		auto texUnit = ScOpenGL::TextureUnit::getNewInstance();
		texUnit->bind();
		texUnit->bindTexture(texture);

		ImageData2D data = create2DImageData(aiTex);

		texUnit->loadTexture(data);

		stbi_image_free(data.pixels);
		return texture;
	}

	void parseMeshIndices(const aiScene& scene, const aiMesh& aiMesh, SComponent::Mesh& mesh) {
		if (aiMesh.HasFaces()) {
			std::vector<unsigned int> indices;
			indices.reserve(((uint64_t)aiMesh.mNumFaces) * ((uint64_t)3));

			for (unsigned int i = 0; i < aiMesh.mNumFaces; i++) {
				aiFace face = aiMesh.mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++) {
					indices.emplace_back(face.mIndices[j]);
				}
			}

			mesh.setIndices(std::move(indices));
			mesh.bufferIndices();
		}
		else {
			//TODO: This is not necessarily an error, should be mended in the future
			throw std::runtime_error("No index data found.");
		}
	}

	//TODO: this function is long, should be broken down into smaller components
	void parseSceneMaterials(const aiScene& scene, const aiMesh& aiMesh, SComponent::Entity& entity) {
		if (scene.HasMaterials()) {

			int materialIndex = aiMesh.mMaterialIndex;
			const auto& aiMaterial = scene.mMaterials[materialIndex];

			float roughness, metalness;

			auto albedoTexCount = aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);

			//const auto albedoLoadRes = aiMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, );

			entity.addComponent<SComponent::Material>();
			SComponent::Material& ctMat = entity.getComponent<SComponent::Material>();


			if (albedoTexCount > 0) {
				aiString path;
				const auto albedoLoadRes = aiMaterial->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &path);
				if (albedoLoadRes == aiReturn_FAILURE) {
					//TODO: has texture but failed to load for some reason, to be logged when logger will be written
				}
				std::string strPath(path.C_Str());
				if (strPath[0] == '*') {
					std::shared_ptr<ScOpenGL::Texture2D> texture = transferTextureToOpenGL(scene, strPath);

					ctMat.albedo = texture;
					entity.getTextures().push_back(texture);
				}
				else {
					//TODO: load texture from file system...
				}
			}
			else {
				aiColor3D baseColor;
				const auto baseColorLoadRes = aiMaterial->Get(AI_MATKEY_BASE_COLOR, baseColor);
				if (baseColorLoadRes == aiReturn_FAILURE) {
					throw std::runtime_error("Material has neither albedo texture, nor color!");
				}
				ctMat.albedo = ScMath::Vector3(baseColor.r, baseColor.g, baseColor.b);
			}

			const auto hasMetalness = aiMaterial->Get(AI_MATKEY_METALLIC_FACTOR, metalness);
			if (hasMetalness == aiReturn_FAILURE) {
				throw std::runtime_error("Could not load material metalness!");
			}
			else {
				ctMat.metalness = metalness;
			}

#pragma warning (push)
#pragma warning (disable : 4244)
			const auto hasRoughness = aiMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
			if (hasRoughness == aiReturn_FAILURE) {
				throw std::runtime_error("Could not load material roughness!");
			}
			else {
				ctMat.smoothness = 1.0 - roughness;
			}
#pragma warning (pop)

			//const auto emissions = aiMaterial->GetTextureCount(aiTextureType_EMISSION_COLOR);
			auto emissiveTexCount = aiMaterial->GetTextureCount(aiTextureType_EMISSIVE);
			if (emissiveTexCount > 0) {
				aiString path;
				const auto emissionTexLoadRes = aiMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &path);
				if (emissionTexLoadRes == aiReturn_SUCCESS) {
					std::string strPath(path.C_Str());
					if (strPath[0] == '*') {
						std::shared_ptr<ScOpenGL::Texture2D> texture = transferTextureToOpenGL(scene, strPath);

						ctMat.emission = texture;
						entity.getTextures().push_back(texture);
					}
					else {
						//try to load emissive vector
					}
				}
				else {
					//TODO: log that material has emission texture, but could not be loaded
				}
			}
		}
	}

	void processNode(const aiScene& scene, const aiNode& node, SComponent::Entity& entity) {
		auto& meshes = entity.getMeshes();

		if (node.mNumMeshes > 1) {
			throw std::runtime_error("Scram doesn't support multiple meshes per single node.");
		}

		for (unsigned int i = 0; i < node.mNumMeshes; i++) {

			const auto& aiMesh = *scene.mMeshes[node.mMeshes[i]];

			SComponent::Mesh mesh;
			parseMeshVertices(aiMesh, mesh);
			parseMeshIndices(scene, aiMesh, mesh);

			parseSceneMaterials(scene, aiMesh, entity);

			entity.addComponent<SComponent::Mesh>(std::move(mesh));
		}

		for (int i = 0; i < node.mNumChildren; i++) {
			auto subEntity = entity.createChild();
			processNode(scene, *node.mChildren[i], *subEntity);
		}

	}

	void parseScene(const aiScene& scene, SComponent::Entity& rootEntity) {

		const auto& rootNode = *scene.mRootNode;

		processNode(scene, rootNode, rootEntity);
	}

	std::shared_ptr<SComponent::Entity> importModelFromFile(const std::string& path) {
		Assimp::Importer importer;
		std::ifstream in(path.c_str());

		if (!in.fail()) {
			in.close();
		}
		else {
			std::string message = "Could not load file:" + path;
			throw std::runtime_error(message.c_str());
		}

		//more postprocess flags: https://documentation.help/assimp/postprocess_8h.html#a64795260b95f5a4b3f3dc1be4f52e410
		const aiScene* scenePtr = importer.ReadFile(path, aiProcess_ValidateDataStructure);
		if (!scenePtr) {
			std::string message = "Scene could not load for file: " + path;
			throw std::runtime_error(message.c_str());
		}

		auto& scene = *scenePtr;

		std::shared_ptr<SComponent::Entity> entity = std::make_shared<SComponent::Entity>();

		parseScene(scene, *entity);
		entity->setId(path);

		return entity;
	}
}
