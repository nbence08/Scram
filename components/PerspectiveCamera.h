#pragma once
#include "core/Preprocess_Definitions.h"
#include "core/math/linear_algebra.hpp"
#include "Camera.h"
#include "ComponentBase.hpp"

class PerspectiveCamera : public Camera<PerspectiveCamera>{
	real_t fov;
	real_t aspect;

	double xDeg, yDeg;

public:
	PerspectiveCamera();

	PerspectiveCamera(const Smath::Vector4& position,
		const Smath::Vector4& forward,
		const Smath::Vector4& up,
		const real_t fov,
		const real_t aspect,
		const real_t nearPlane,
		const real_t farPlane);

	void updateForward(double diffX, double diffY);

	inline real_t getFov() {return fov;}
	inline void setFov(const real_t fov) {this->fov = fov;}

	inline real_t getAspect(){return aspect;}
	inline void setAspect(const real_t aspect){this->aspect = aspect;}

	Smath::Matrix4 view();

	Smath::Matrix4 projection();
};

