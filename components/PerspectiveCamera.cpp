#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() {
	position = Vector4(0.0f, 0.0f, 2.0f, 1.0f);
	forward = Vector4(0.0f, 0.0f, -1.0f, 0.0f);
	up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	fov = 80.0f;
	aspect = 800.0 / 600.0;
	nearPlane = 0.01;
	farPlane = 100.0;
}

PerspectiveCamera::PerspectiveCamera(const Vector4& position,
	const Vector4& forward,
	const Vector4& up,
	const real_t fov,
	const real_t aspect,
	const real_t nearPlane,
	const real_t farPlane) :
	position(position), forward(forward), up(up),
	fov(fov), aspect(aspect),
	nearPlane(nearPlane), farPlane(farPlane)
{}

Matrix4 PerspectiveCamera::view() {
	Vector3 p = math::homogenDivide(position);
	return math::getLookAt(forward , up, p);
}

Matrix4 PerspectiveCamera::perspective() {
	return math::perspective(fov, aspect, nearPlane, farPlane);
}