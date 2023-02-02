#pragma once
#include "core/math/Vector3.hpp"
#include "ComponentBase.hpp"

class SpotLight : public ComponentBase{
public:

	Vector3 intensity;
	Vector3 attenuation;
	Vector3 position;
	Vector3 direction;

	float dimAngle;
	float angle;
};

