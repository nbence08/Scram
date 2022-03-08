#pragma once
#include "core/math/Vector3.h"
#include "ComponentBase.hpp"

class SpotLight : public ComponentBase{
public:

	SMath::Vector3 intensity;
	SMath::Vector3 attenuation;
	SMath::Vector3 position;
	SMath::Vector3 direction;

	float dimAngle;
	float angle;
};

