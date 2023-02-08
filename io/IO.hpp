#pragma once
#include <fstream>
#include <iterator>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb/stb_image.h"

#include "assimp/Importer.hpp" 
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Struct_Definitions.hpp"

#include "Entity.hpp"
#include "TextureUnit.hpp"
#include "Material.hpp"

namespace ScIO{
	//reads a file of path given as parameter
	//throws std::ios_base::failure if 
	std::string readFile(const std::string& path);

	ImageData2D readImage(const std::string& path);

	void freeImage(ImageData2D& data);

	void parseMeshVertices(const aiMesh& aiMesh, SComponent::Mesh& mesh);

	ImageData2D create2DImageData(aiTexture& aiTex);

	std::shared_ptr<ScOpenGL::Texture2D> transferTextureToOpenGL(const aiScene& scene, std::string& strPath);

	void parseMeshIndices(const aiScene& scene, const aiMesh& aiMesh, SComponent::Mesh& mesh);

	//TODO: this function is long, should be broken down into smaller components
	void parseSceneMaterials(const aiScene& scene, const aiMesh& aiMesh, SComponent::Entity& entity);

	void processNode(const aiScene& scene, const aiNode& node, SComponent::Entity& entity);

	void parseScene(const aiScene& scene, SComponent::Entity& rootEntity);

	std::shared_ptr<SComponent::Entity> importModelFromFile(const std::string& path);
};
