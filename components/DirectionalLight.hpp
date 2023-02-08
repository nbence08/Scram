#pragma once
#include "Vector3.hpp"
#include "Math_Functions.hpp"
#include "Texture2D.hpp"
#include "Global_Props.hpp"
#include "ComponentBase.hpp"

namespace SComponent {

	class DirectionalLight : public ComponentBase {
	public:

		Smath::Vector3 intensity;
		//direction of fragments to light source
		Smath::Vector3 direction;
		std::shared_ptr<ScOpenGL::Texture2D> shadowMap;

		Smath::Matrix4 getLightSpaceMatrix() const;

		DirectionalLight();

		inline bool hasShadowMap() const {
			return shadowMap.get() != nullptr;
		}
	};
}

