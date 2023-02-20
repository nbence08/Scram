#pragma once

#include <vector>

#include "TextureCube.hpp"
#include "linear_algebra.hpp"
#include "ComponentBase.hpp"
#include "Global_Props.hpp"

namespace SComponent {
	class PointLight : public ComponentBase {
	public:

		ScMath::Vector3 intensity;
		ScMath::Vector3 attenuation;

		ScMath::Vector3 position;

		real_t farPlane;
		std::shared_ptr<ScOpenGL::TextureCube> shadowMap;

		PointLight();

		inline bool hasShadowMap() const {
			return shadowMap.get() != nullptr;
		}

		std::vector<ScMath::Matrix4> getLightSpaceMatrices() const;
	};
}
