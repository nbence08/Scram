#pragma once
#include "core/Preprocess_Definitions.h"
#include "linear_algebra.hpp"
#include "Quaternion.h"

namespace math {
	static inline double toRadians(double degree) {
		return degree *= (PI/180.0);
	}
	static inline double toDegrees(double radians) {
		return radians *= (180.0/PI);
	}



	static SMath::Matrix4 translate(const SMath::Vector3& translation) {
		SMath::Vector4 offset(translation, 1.0);

		SMath::Vector4 e1(1.0, 0.0, 0.0, 0.0);
		SMath::Vector4 e2(0.0, 1.0, 0.0, 0.0);
		SMath::Vector4 e3(0.0, 0.0, 1.0, 0.0);

		return SMath::Matrix4(e1, e2, e3, offset);
	}

	static SMath::Matrix4 translate(real_t x, real_t y, real_t z) {
		return translate(SMath::Vector3(x, y, z));
	}

	static SMath::Matrix4 rotate(const double arc, const SMath::Vector3& axis) {
		auto rotMat3 = SMath::Quaternion::rotation(arc, axis).getRotationMatrix();
		return SMath::Matrix4(rotMat3);
	}

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static SMath::Matrix4 scale(const double x, const double y, const double z) {
		return SMath::Matrix4(x, 0.0, 0.0, 0.0,
					   0.0, y, 0.0, 0.0,
					   0.0, 0.0, z, 0.0,
					   0.0, 0.0, 0.0, 1);
	}
	#pragma warning(pop)

	static SMath::Vector3 homogenDivide(const SMath::Vector4& vec4) {
		if (vec4.w == 1.0f) return SMath::Vector3(vec4.x, vec4.y, vec4.z);
		else return SMath::Vector3(vec4.x / vec4.w, vec4.y / vec4.w, vec4.z / vec4.w);
	}

	static SMath::Matrix4 diag4(const real_t value) {
		return SMath::Matrix4(value, 0, 0, 0,
					   0, value, 0, 0,
					   0, 0, value, 0,
					   0, 0, 0, value);
	}

	static SMath::Matrix4 getLookAt(const SMath::Vector3& forward, const SMath::Vector3& up, const SMath::Vector3& pos) {
		//UVN coordinate system
		SMath::Vector3 N(forward);
		SMath::Vector3 V(up);
		SMath::Vector3 U = cross(N, V);	//right

		N.normalize();
		V.normalize();
		U.normalize();

		auto tx = dot(U, pos);
		auto ty = dot(V, pos);
		auto tz = dot(N, pos);

		return SMath::Matrix4(
			U.x, U.y, U.z, -tx,
			V.x, V.y, V.z, -ty,
			N.x, N.y, N.z, -tz,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static SMath::Matrix4 orthographic(real_t l, real_t r, real_t t, real_t b, real_t n, real_t f) {
		real_t r_l = r-l;
		real_t t_b = t-b;
		real_t f_n = f-n;

		return SMath::Matrix4(
			2.0/r_l, 0, 0, -(r+l)/r_l,
			0, 2.0/t_b, 0, -(t+b)/t_b,
			0, 0, 2.0/f_n, -(f+n)/f_n,
			0, 0, 0,				1
		);
	}
	#pragma warning (pop)

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static SMath::Matrix4 perspective(real_t fov, real_t aspect, real_t nearPlane, real_t farPlane) {
		real_t fovDiv2 = math::toRadians(((double)fov) / 2.0);
		real_t x = 1.0 / (tan((double)fovDiv2) * aspect);
		real_t y = 1.0 / (tan(fovDiv2));
		real_t A = -(nearPlane + farPlane) / (nearPlane - farPlane);
		real_t B = 2.0 * ((double)nearPlane * (double)farPlane) / ((double)nearPlane - (double)farPlane);
		return SMath::Matrix4(
			x, 0.0, 0.0, 0.0,
			0.0, y, 0.0, 0.0,
			0.0, 0.0, A, B,
			0.0, 0.0, 1.0, 0.0
		);
	}
	#pragma warning (pop)
}