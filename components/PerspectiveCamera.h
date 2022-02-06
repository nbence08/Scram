#pragma once
#include "core/Preprocess_Definitions.h"
#include "core/math/linear_algebra.hpp"
#include "Camera.h"

class PerspectiveCamera : public Camera<PerspectiveCamera>{
	real_t fov;
	real_t aspect;

public:
	PerspectiveCamera();

	PerspectiveCamera(const Vector4& position,
		const Vector4& forward,
		const Vector4& up,
		const real_t fov,
		const real_t aspect,
		const real_t nearPlane,
		const real_t farPlane);

	inline real_t getFov() {return fov;}
	inline void setFov(const real_t fov) {this->fov = fov;}

	inline real_t getAspect(){return aspect;}
	inline void setAspect(const real_t aspect){this->aspect = aspect;}

	Matrix4 view();

	Matrix4 projection();
};

