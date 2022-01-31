#pragma once
#include "Mesh.h"
#include "core/math/linear_algebra.hpp"
#include "core/OpenGL/Texture2D.h"

class Mesh;

class Model{
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<std::shared_ptr<Texture2D>> textures;

public:
	inline std::vector<std::shared_ptr<Mesh>>& getMeshes(){ return meshes; }
	inline std::vector<std::shared_ptr<Texture2D>>& getTextures() { return textures; }
	Matrix4 model;
};

