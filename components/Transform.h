#pragma once
#include "core/math/linear_algebra.hpp"
#include "core/math/Quaternion.h"
#include "ComponentBase.hpp"

class Transform : public ComponentBase{
	//rotation around x, y, z axes
	SMath::Vector3 translation;
	SMath::Vector3 rotation;
	SMath::Vector3 scale;
public:

	Transform(): scale(SMath::Vector3(1.0, 1.0, 1.0)), rotation(SMath::Vector3(0.0, 0.0, 0.0)), translation(SMath::Vector3(0.0, 0.0, 0.0)) {}

	Transform(const SMath::Vector3& translation, const SMath::Vector3& rotation, const SMath::Vector3& scale):
			scale(scale), rotation(rotation), translation(translation) {}

	SMath::Matrix4 model() {
		return SMath::translate(translation)*
			SMath::rotate(rotation.x, SMath::Vector3(1.0, 0.0, 0.0))*
			SMath::rotate(rotation.y, SMath::Vector3(0.0, 1.0, 0.0))*
			SMath::rotate(rotation.z, SMath::Vector3(0.0, 0.0, 1.0))*
			SMath::scale(scale.x, scale.y, scale.z);
	}

	void setScale(const SMath::Vector3& scale){ this->scale = scale; }
	void setTranslation(const SMath::Vector3& translation) { this->translation = translation; }
	void setRotation(const SMath::Vector3& rotation) { this->rotation = rotation; }
};