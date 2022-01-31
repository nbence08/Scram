#pragma once
#include "core/Preprocess_Definitions.h"
#include "core/math/linear_algebra.hpp"

class PerspectiveCamera{
	Vector4 position;
	Vector4 forward;
	Vector4 up;
	real_t fov;
	real_t aspect;
	real_t nearPlane;
	real_t farPlane;

public:
	PerspectiveCamera();

	PerspectiveCamera(const Vector4& position,
		const Vector4& forward,
		const Vector4& up,
		const real_t fov,
		const real_t aspect,
		const real_t nearPlane,
		const real_t farPlane);

	inline Vector4 getPosition() const { return position; }
	inline void setPosition(const Vector4& pos) { position = pos;}
	inline void translatePosition(const Vector4& offset) { position += offset; }
	inline void moveForward(const real_t offset) { position += forward * offset; }
	inline void moveBackward(const real_t offset) { moveForward(-offset); }
	inline void moveRightward(const real_t offset) {
		Vector3 up(0.0f, 1.0f, 0.0f);
		Vector3 right = cross(forward, up);
		right.normalize();

		position += Vector4(right.x, right.y, right.z, 0.0) * (offset);
	}
	inline void moveLeftward(const real_t offset) { moveRightward(-offset); }


	inline Vector4 getForward() const { return forward; }
	inline void setForward(const Vector4& forward) { this->forward = forward.normalized(); }

	inline Vector4 getUp() const { return up; }
	inline void setUp(const Vector4& up) { this->up = up.normalized(); }

	inline real_t getFov() {return fov;}
	inline void setFov(const real_t fov) {this->fov = fov;}

	inline real_t getAspect(){return aspect;}
	inline void setAspect(const real_t aspect){this->aspect = aspect;}

	inline real_t getNearPlane() const { return nearPlane; }
	inline void setNearPlane(const real_t nearPlane){this->nearPlane = nearPlane; }

	inline real_t getFarPlane() const { return farPlane; }
	inline void setFarPlane(const real_t farPlane) {this->farPlane = farPlane; }

	Matrix4 view();

	Matrix4 perspective();
};

