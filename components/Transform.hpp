#pragma once
#include "linear_algebra.hpp"
#include "Quaternion.hpp"
#include "ComponentBase.hpp"

#include "components_export.hpp"

namespace SComponent {
	class COMPONENTS_EXPORT Transform : public ComponentBase {
		//rotation around x, y, z axes
		ScMath::Vector3 translation;
		ScMath::Vector3 rotation;
		ScMath::Vector3 scale;
	public:

		Transform() : scale(ScMath::Vector3(1.0, 1.0, 1.0)), rotation(ScMath::Vector3(0.0, 0.0, 0.0)), translation(ScMath::Vector3(0.0, 0.0, 0.0)) {}

		Transform(const ScMath::Vector3& translation, const ScMath::Vector3& rotation, const ScMath::Vector3& scale) :
			scale(scale), rotation(rotation), translation(translation) {}

		ScMath::Matrix4 model() {
			return math::translate(translation) *
				math::rotate(rotation.x, ScMath::Vector3(1.0, 0.0, 0.0)) *
				math::rotate(rotation.y, ScMath::Vector3(0.0, 1.0, 0.0)) *
				math::rotate(rotation.z, ScMath::Vector3(0.0, 0.0, 1.0)) *
				math::scale(scale.x, scale.y, scale.z);
		}

		void setScale(const ScMath::Vector3& scale) { this->scale = scale; }
		void setTranslation(const ScMath::Vector3& translation) { this->translation = translation; }
		void setRotation(const ScMath::Vector3& rotation) { this->rotation = rotation; }
	};
}
