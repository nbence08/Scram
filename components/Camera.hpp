#pragma once
#include "linear_algebra.hpp"
#include "ComponentBase.hpp"

namespace SComponent {
	template <typename T>
	class Camera : public ComponentBase {
	protected:
		Smath::Vector4 position;
		Smath::Vector4 forward;
		Smath::Vector4 up;
		real_t nearPlane;
		real_t farPlane;

	public:


		Camera(const Smath::Vector4& position = Smath::Vector4(0.0, 0.0, 0.0),
			const Smath::Vector4& forward = Smath::Vector4(0.0, 0.0, -1.0),
			const Smath::Vector4& up = Smath::Vector4(0.0, 1.0, 0.0),
			const real_t nearPlane = 1.0,
			const real_t farPlane = 500.0) :position(position), forward(forward), up(up),
			nearPlane(nearPlane), farPlane(farPlane) {};

		inline Smath::Vector4 getPosition() const { return position; }
		inline void setPosition(const Smath::Vector4& pos) { position = pos; }
		inline void translatePosition(const Smath::Vector4& offset) { position += offset; }
		inline void moveForward(const real_t offset) { position += forward * offset; }
		inline void moveBackward(const real_t offset) { moveForward(-offset); }
		inline void moveRightward(const real_t offset) {
			Smath::Vector3 up(0.0f, 1.0f, 0.0f);
			Smath::Vector3 right = cross(forward, up);
			right.normalize();

			position += Smath::Vector4(right.x, right.y, right.z, 0.0) * (offset);
		}
		inline void moveLeftward(const real_t offset) { moveRightward(-offset); }


		inline Smath::Vector4 getForward() const { return forward; }
		inline void setForward(const Smath::Vector4& forward) { this->forward = forward.normalized(); }

		inline Smath::Vector4 getUp() const { return up; }
		inline void setUp(const Smath::Vector4& up) { this->up = up.normalized(); }

		inline real_t getNearPlane() const { return nearPlane; }
		inline void setNearPlane(const real_t nearPlane) { this->nearPlane = nearPlane; }

		inline real_t getFarPlane() const { return farPlane; }
		inline void setFarPlane(const real_t farPlane) { this->farPlane = farPlane; }

		inline void updateForward(double xDiff, double yDiff) {
			T& t = static_cast<T>(*this);
			t.updateForward(xDiff, yDiff);
		}

		Smath::Matrix4 view() {
			T& t = static_cast<T>(*this);
			return t.view();
		};

		Smath::Matrix4 projection() {
			T& t = static_cast<T>(*this);
			return t.projection();
		};
	};
}
