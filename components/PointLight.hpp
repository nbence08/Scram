#pragma once

#include <vector>

#include "TextureCube.hpp"
#include "linear_algebra.hpp"
#include "ComponentBase.hpp"
#include "Global_Props.hpp"

class PointLight : public ComponentBase{
public:

	Vector3 intensity;
	Vector3 attenuation;

	Vector3 position;

	real_t farPlane;
	std::shared_ptr<TextureCube> shadowMap;

	PointLight();

	inline bool hasShadowMap() const {
		return shadowMap.get() != nullptr;
	}

	std::vector<Matrix4> getLightSpaceMatrices() const;
};

