#pragma once
#include "core/math/Vector3.h"

class DirectionalLight{
public:
	Vector3 intensity;
	//direction of fragments to light source
	Vector3 direction;
};

