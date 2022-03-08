#pragma once
#include "core/Preprocess_Definitions.h"
#include "core/math/linear_algebra.hpp"
#include "Camera.h"
#include "ComponentBase.hpp"

class PerspectiveCamera : public Camera<PerspectiveCamera>{
	real_t fov;
	real_t aspect;

public:
	PerspectiveCamera();

	PerspectiveCamera(const  SMath::Vector4& position,
		const  SMath::Vector4& forward,
		const  SMath::Vector4& up,
		const real_t fov,
		const real_t aspect,
		const real_t nearPlane,
		const real_t farPlane);

	inline real_t getFov() {return fov;}
	inline void setFov(const real_t fov) {this->fov = fov;}

	inline real_t getAspect(){return aspect;}
	inline void setAspect(const real_t aspect){this->aspect = aspect;}

	SMath::Matrix4 view();

	SMath::Matrix4 projection();
};

