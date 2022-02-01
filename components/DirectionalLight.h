#pragma once
#include "core/math/Vector3.h"
#include "core/math/Math_Functions.hpp"
#include "core/OpenGL/Texture2D.h"
#include "core/Global_Props.hpp"

//this will be managable, and most definitely not a const in the future
const real_t ORTHOGONAL_EDGE_SIZE = 400;

class DirectionalLight {
public:
	Vector3 intensity;
	//direction of fragments to light source
	Vector3 direction;
	std::shared_ptr<Texture2D> shadowMap;

	Matrix4 getLightSpaceMatrix() const;

	DirectionalLight();
};

