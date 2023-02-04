#pragma once
#include "core/math/Vector3.hpp"
#include "ComponentBase.hpp"

class SpotLight : public ComponentBase{
public:

	Smath::Vector3 intensity;
	Smath::Vector3 attenuation;
	Smath::Vector3 position;
	Smath::Vector3 direction;

	float dimAngle;
	float angle;
};

