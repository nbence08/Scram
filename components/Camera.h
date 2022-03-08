#pragma once
#include "core/math/linear_algebra.hpp"
#include "ComponentBase.hpp"

template <typename T>
class Camera : public ComponentBase{
protected:
	 SMath::Vector4 position;
	 SMath::Vector4 forward;
	 SMath::Vector4 up;
	real_t nearPlane;
	real_t farPlane;

public:


	Camera(const  SMath::Vector4& position =  SMath::Vector4(0.0, 0.0, 0.0),
		   const  SMath::Vector4& forward =  SMath::Vector4(0.0, 0.0, -1.0),
		   const  SMath::Vector4& up =  SMath::Vector4(0.0, 1.0, 0.0),
		   const real_t nearPlane = 1.0,
		   const real_t farPlane = 500.0):position(position), forward(forward), up(up),
		nearPlane(nearPlane), farPlane(farPlane) {};

	inline  SMath::Vector4 getPosition() const { return position; }
	inline void setPosition(const  SMath::Vector4& pos) { position = pos; }
	inline void translatePosition(const  SMath::Vector4& offset) { position += offset; }
	inline void moveForward(const real_t offset) { position += forward * offset; }
	inline void moveBackward(const real_t offset) { moveForward(-offset); }
	inline void moveRightward(const real_t offset) {
		SMath::Vector3 up(0.0f, 1.0f, 0.0f);
		SMath::Vector3 right = cross(forward, up);
		right.normalize();

		position +=  SMath::Vector4(right.x, right.y, right.z, 0.0) * (offset);
	}
	inline void moveLeftward(const real_t offset) { moveRightward(-offset); }


	inline  SMath::Vector4 getForward() const { return forward; }
	inline void setForward(const  SMath::Vector4& forward) { this->forward = forward.normalized(); }

	inline  SMath::Vector4 getUp() const { return up; }
	inline void setUp(const  SMath::Vector4& up) { this->up = up.normalized(); }

	inline real_t getNearPlane() const { return nearPlane; }
	inline void setNearPlane(const real_t nearPlane) { this->nearPlane = nearPlane; }

	inline real_t getFarPlane() const { return farPlane; }
	inline void setFarPlane(const real_t farPlane) { this->farPlane = farPlane; }

	SMath::Matrix4 view() {
		T& t = static_cast<T>(*this);
		return t.view();
	};

	SMath::Matrix4 projection() {
		T& t = static_cast<T>(*this);
		return t.projection();
	};
};