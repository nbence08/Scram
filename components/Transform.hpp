#pragma once
#include "core/math/linear_algebra.hpp"
#include "core/math/Quaternion.hpp"
#include "ComponentBase.hpp"

class Transform : public ComponentBase{
	//rotation around x, y, z axes
	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;
public:

	Transform(): scale(Vector3(1.0, 1.0, 1.0)), rotation(Vector3(0.0, 0.0, 0.0)), translation(Vector3(0.0, 0.0, 0.0)) {}

	Transform(const Vector3& translation, const Vector3& rotation, const Vector3& scale):
			scale(scale), rotation(rotation), translation(translation) {}

	Matrix4 model() {
		return math::translate(translation)*
			   math::rotate(rotation.x, Vector3(1.0, 0.0, 0.0))*
			   math::rotate(rotation.y, Vector3(0.0, 1.0, 0.0))*
			   math::rotate(rotation.z, Vector3(0.0, 0.0, 1.0))*
			   math::scale(scale.x, scale.y, scale.z);
	}

	void setScale(const Vector3& scale){ this->scale = scale; }
	void setTranslation(const Vector3& translation) { this->translation = translation; }
	void setRotation(const Vector3& rotation) { this->rotation = rotation; }
};