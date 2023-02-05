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

namespace IO{
	//reads a file of path given as parameter
	//throws std::ios_base::failure if 
	std::string readFile(const std::string& path);

	ImageData2D readImage(const std::string& path);

	void freeImage(ImageData2D& data);

	void parseMeshVertices(const aiMesh& aiMesh, Mesh& mesh);

	ImageData2D create2DImageData(aiTexture& aiTex);

	std::shared_ptr<Texture2D> transferTextureToOpenGL(const aiScene& scene, std::string& strPath);

	void parseMeshIndices(const aiScene& scene, const aiMesh& aiMesh, Mesh& mesh);

	//TODO: this function is long, should be broken down into smaller components
	void parseSceneMaterials(const aiScene& scene, const aiMesh& aiMesh, Entity& entity);

	void processNode(const aiScene& scene, const aiNode& node, Entity& entity);

	void parseScene(const aiScene& scene, Entity& rootEntity);

	std::shared_ptr<Entity> importModelFromFile(const std::string& path);
};
