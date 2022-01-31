#pragma once
#include "core/math/Vector3.h"

class SpotLight{
public:
	Vector3 intensity;
	Vector3 attenuation;
	Vector3 position;
	Vector3 direction;

	float dimAngle;
	float angle;
};

