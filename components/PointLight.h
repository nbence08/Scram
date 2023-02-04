#pragma once

#include <vector>

#include "core/OpenGL/TextureCube.h"
#include "core/math/linear_algebra.hpp"
#include "ComponentBase.hpp"
#include "core/Global_Props.hpp"

class PointLight : public ComponentBase{
public:

	Smath::Vector3 intensity;
	Smath::Vector3 attenuation;

	Smath::Vector3 position;

	real_t farPlane;
	std::shared_ptr<TextureCube> shadowMap;

	PointLight();

	inline bool hasShadowMap() const {
		return shadowMap.get() != nullptr;
	}

	std::vector<Smath::Matrix4> getLightSpaceMatrices() const;
};

