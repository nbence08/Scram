#pragma once
#include "core/math/linear_algebra.hpp"
#include "core/math/Quaternion.h"
#include "ComponentBase.hpp"

class Transform : public ComponentBase{
	//rotation around x, y, z axes
	Smath::Vector3 translation;
	Smath::Vector3 rotation;
	Smath::Vector3 scale;
public:

	Transform(): scale(Smath::Vector3(1.0, 1.0, 1.0)), rotation(Smath::Vector3(0.0, 0.0, 0.0)), translation(Smath::Vector3(0.0, 0.0, 0.0)) {}

	Transform(const Smath::Vector3& translation, const Smath::Vector3& rotation, const Smath::Vector3& scale):
			scale(scale), rotation(rotation), translation(translation) {}

	Smath::Matrix4 model() {
		return math::translate(translation)*
			   math::rotate(rotation.x, Smath::Vector3(1.0, 0.0, 0.0))*
			   math::rotate(rotation.y, Smath::Vector3(0.0, 1.0, 0.0))*
			   math::rotate(rotation.z, Smath::Vector3(0.0, 0.0, 1.0))*
			   math::scale(scale.x, scale.y, scale.z);
	}

	void setScale(const Smath::Vector3& scale){ this->scale = scale; }
	void setTranslation(const Smath::Vector3& translation) { this->translation = translation; }
	void setRotation(const Smath::Vector3& rotation) { this->rotation = rotation; }
};