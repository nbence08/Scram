#pragma once
#include "Vector3.hpp"
#include "ComponentBase.hpp"

namespace SComponent {
	class SpotLight : public ComponentBase {
	public:

		ScMath::Vector3 intensity;
		ScMath::Vector3 attenuation;
		ScMath::Vector3 position;
		ScMath::Vector3 direction;

		float dimAngle;
		float angle;
	};
}
