#pragma once
#include "core/math/Vector3.h"

class PointLight{
public:
	Vector3 intensity;
	Vector3 attenuation;

	Vector3 position;
};

