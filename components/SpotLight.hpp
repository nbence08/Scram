#pragma once
#include "Vector3.hpp"
#include "ComponentBase.hpp"

#include "components_export.hpp"

namespace SComponent {
	class COMPONENTS_EXPORT SpotLight : public ComponentBase {
	public:

		ScMath::Vector3 intensity;
		ScMath::Vector3 attenuation;
		ScMath::Vector3 position;
		ScMath::Vector3 direction;

		float dimAngle;
		float angle;
	};
}
