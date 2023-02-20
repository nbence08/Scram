#include "PerspectiveCamera.hpp"

namespace SComponent {
	PerspectiveCamera::PerspectiveCamera() {
		position = ScMath::Vector4(0.0f, 0.0f, 2.0f, 1.0f);
		forward = ScMath::Vector4(0.0f, 0.0f, -1.0f, 0.0f);
		up = ScMath::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
		fov = 80.0f;
		aspect = (real_t)(800.0 / 600.0);
		nearPlane = (real_t)0.01;
		farPlane = 100.0;
		xDeg = 0.0;
		yDeg = 0.0;
	}

	PerspectiveCamera::PerspectiveCamera(const ScMath::Vector4& position,
		const ScMath::Vector4& forward,
		const ScMath::Vector4& up,
		const real_t nearPlane,
		const real_t farPlane,
		const real_t fov,
		const real_t aspect) :
		fov(fov), aspect(aspect), Camera(position, forward, up, nearPlane, farPlane) {
		xDeg = 0.0;
		yDeg = 0.0;
	}

	/// <summary>
	/// Updates the forward vector by rotating the ray, along which the camera views the world.
	/// </summary>
	/// <param name="diffX">Difference in horizontal orientation</param>
	/// <param name="diffY">Difference in vertical orientation</param>
	void PerspectiveCamera::updateForward(double diffX, double diffY) {

		ScMath::Vector3 forward(0.0, 0.0, -1.0);
		ScMath::Vector3 up(0.0, 1.0, 0.0);
		ScMath::Vector3 right = cross(forward, up);

		xDeg += diffX;
		yDeg += diffY;

		if (yDeg < -89.0) yDeg = -89.0;
		if (yDeg > 89.0) yDeg = 89.0;

		//std::cout << "X:" << xDeg << " Y:" << yDeg << "\n";

		auto yRot = ScMath::Quaternion::rotation(math::toRadians(yDeg), right).getRotationMatrix();
		auto xRot = ScMath::Quaternion::rotation(math::toRadians(xDeg), up).getRotationMatrix();


		ScMath::Vector3 newForward = xRot * (yRot * forward);
		ScMath::Vector3 newUp = xRot * (yRot * up);

		setForward(ScMath::Vector4(newForward.x, newForward.y, newForward.z, 0.0));
		setUp(ScMath::Vector4(newUp.x, newUp.y, newUp.z, 0.0));
	}

	ScMath::Matrix4 PerspectiveCamera::view() {
		ScMath::Vector3 p = math::homogenDivide(position);
		return math::getLookAt(forward, up, p);
	}

	ScMath::Matrix4 PerspectiveCamera::projection() {
		return math::perspective(fov, aspect, nearPlane, farPlane);
	}
}
