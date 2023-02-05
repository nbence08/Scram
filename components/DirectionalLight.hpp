#pragma once
#include "Vector3.hpp"
#include "Math_Functions.hpp"
#include "Texture2D.hpp"
#include "Global_Props.hpp"
#include "ComponentBase.hpp"

class DirectionalLight : public ComponentBase {
public:

	Vector3 intensity;
	//direction of fragments to light source
	Vector3 direction;
	std::shared_ptr<Texture2D> shadowMap;

	Matrix4 getLightSpaceMatrix() const;

	DirectionalLight();

	inline bool hasShadowMap() const {
		return shadowMap.get() != nullptr;
	}
};

