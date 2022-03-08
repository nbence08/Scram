#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() {
	position =  SMath::Vector4(0.0f, 0.0f, 2.0f, 1.0f);
	forward =  SMath::Vector4(0.0f, 0.0f, -1.0f, 0.0f);
	up =  SMath::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	fov = 80.0f;
	aspect = (real_t) (800.0 / 600.0);
	nearPlane = (real_t) 0.01;
	farPlane = 100.0;
}

PerspectiveCamera::PerspectiveCamera(const  SMath::Vector4& position,
	const  SMath::Vector4& forward,
	const  SMath::Vector4& up,
	const real_t nearPlane,
	const real_t farPlane,
	const real_t fov,
	const real_t aspect):
	fov(fov), aspect(aspect), Camera(position, forward, up, nearPlane, farPlane) {}

SMath::Matrix4 PerspectiveCamera::view() {
	SMath::Vector3 p = SMath::homogenDivide(position);
	return SMath::getLookAt(forward , up, p);
}

SMath::Matrix4 PerspectiveCamera::projection() {
	return SMath::perspective(fov, aspect, nearPlane, farPlane);
}