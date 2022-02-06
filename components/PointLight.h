#pragma once
#include "core/math/Vector3.h"
#include "ComponentBase.hpp"

class PointLight : public ComponentBase{
public:
	int getTypeId() override {
		return getComponentTypeId<PointLight>();
	}

	Vector3 intensity;
	Vector3 attenuation;

	Vector3 position;
};

