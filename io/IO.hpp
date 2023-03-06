#pragma once
#include <fstream>
#include <iterator>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "IO_export.hpp"

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
	std::string IO_EXPORT readFile(const std::string& path);

	ImageData2D IO_EXPORT readImage(const std::string& path);

	void IO_EXPORT freeImage(ImageData2D& data);

	void IO_EXPORT parseMeshVertices(const aiMesh& aiMesh, SComponent::Mesh& mesh);

	ImageData2D IO_EXPORT create2DImageData(aiTexture& aiTex);

	std::shared_ptr<ScOpenGL::Texture2D> IO_EXPORT transferTextureToOpenGL(const aiScene& scene, std::string& strPath);

	void IO_EXPORT parseMeshIndices(const aiScene& scene, const aiMesh& aiMesh, SComponent::Mesh& mesh);

	//TODO: this function is long, should be broken down into smaller components
	void IO_EXPORT parseSceneMaterials(const aiScene& scene, const aiMesh& aiMesh, SComponent::Entity& entity);

	void IO_EXPORT processNode(const aiScene& scene, const aiNode& node, SComponent::Entity& entity);

	void IO_EXPORT parseScene(const aiScene& scene, SComponent::Entity& rootEntity);

	std::shared_ptr<SComponent::Entity> IO_EXPORT importModelFromFile(const std::string& path);
};
