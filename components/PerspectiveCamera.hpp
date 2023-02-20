#pragma once
#include "Preprocess_Definitions.hpp"
#include "linear_algebra.hpp"
#include "Camera.hpp"
#include "ComponentBase.hpp"

namespace SComponent {
	class PerspectiveCamera : public Camera<PerspectiveCamera> {
		real_t fov;
		real_t aspect;

		double xDeg, yDeg;

	public:
		PerspectiveCamera();

		PerspectiveCamera(const ScMath::Vector4& position,
			const ScMath::Vector4& forward,
			const ScMath::Vector4& up,
			const real_t fov,
			const real_t aspect,
			const real_t nearPlane,
			const real_t farPlane);

		void updateForward(double diffX, double diffY);

		inline real_t getFov() { return fov; }
		inline void setFov(const real_t fov) { this->fov = fov; }

		inline real_t getAspect() { return aspect; }
		inline void setAspect(const real_t aspect) { this->aspect = aspect; }

		ScMath::Matrix4 view();

		ScMath::Matrix4 projection();
	};
}
