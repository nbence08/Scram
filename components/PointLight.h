#pragma once

#include <vector>
#include "core/OpenGL/TextureCube.h"
#include "core/math/linear_algebra.hpp"
#include "ComponentBase.hpp"
#include "core/Global_Props.hpp"

class PointLight : public ComponentBase{
public:

	SMath::Vector3 intensity;
	SMath::Vector3 attenuation;

	SMath::Vector3 position;

	real_t farPlane;
	std::shared_ptr<TextureCube> shadowMap;

	PointLight();

	inline bool hasShadowMap() const {
		return shadowMap.get() != nullptr;
	}

	std::vector<SMath::Matrix4> getLightSpaceMatrices() const;


};
