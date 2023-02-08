#pragma once

#include <vector>

#include "core/OpenGL/TextureCube.hpp"
#include "core/math/linear_algebra.hpp"
#include "ComponentBase.hpp"
#include "core/Global_Props.hpp"

namespace SComponent {
	class PointLight : public ComponentBase {
	public:

		Smath::Vector3 intensity;
		Smath::Vector3 attenuation;

		Smath::Vector3 position;

		real_t farPlane;
		std::shared_ptr<ScOpenGL::TextureCube> shadowMap;

		PointLight();

		inline bool hasShadowMap() const {
			return shadowMap.get() != nullptr;
		}

		std::vector<Smath::Matrix4> getLightSpaceMatrices() const;
	};
}
