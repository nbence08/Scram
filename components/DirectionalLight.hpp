#pragma once
#include "Vector3.hpp"
#include "Math_Functions.hpp"
#include "Texture2D.hpp"
#include "Global_Props.hpp"
#include "ComponentBase.hpp"

#include "components_export.hpp"

namespace SComponent {

	class COMPONENTS_EXPORT DirectionalLight : public ComponentBase {
	public:

		ScMath::Vector3 intensity;
		//direction of fragments to light source
		ScMath::Vector3 direction;
		std::shared_ptr<ScOpenGL::Texture2D> shadowMap;

		ScMath::Matrix4 getLightSpaceMatrix() const;

		DirectionalLight();

		inline bool hasShadowMap() const {
			return shadowMap.get() != nullptr;
		}
	};
}

