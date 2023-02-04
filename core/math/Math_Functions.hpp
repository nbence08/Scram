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



	static Smath::Matrix4 translate(const Smath::Vector3& translation) {
		Smath::Vector4 offset(translation, 1.0);
		offset.w = 1.0;

		Smath::Vector4 e1(1.0, 0.0, 0.0, 0.0);
		Smath::Vector4 e2(0.0, 1.0, 0.0, 0.0);
		Smath::Vector4 e3(0.0, 0.0, 1.0, 0.0);

		return Smath::Matrix4(e1, e2, e3, offset);
	}

	static Smath::Matrix4 translate(real_t x, real_t y, real_t z) {
		return translate(Smath::Vector3(x, y, z));
	}

	static Smath::Matrix4 rotate(const double arc, const Smath::Vector3& axis) {
		auto rotMat3 = Smath::Quaternion::rotation(arc, axis).getRotationMatrix();
		return Smath::Matrix4(rotMat3);
	}

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static Smath::Matrix4 scale(const double x, const double y, const double z) {
		return Smath::Matrix4(x, 0.0, 0.0, 0.0,
					   0.0, y, 0.0, 0.0,
					   0.0, 0.0, z, 0.0,
					   0.0, 0.0, 0.0, 1);
	}
	#pragma warning(pop)

	static Smath::Vector3 homogenDivide(const Smath::Vector4& vec4) {
		if (vec4.w == 1.0f) return Smath::Vector3(vec4.x, vec4.y, vec4.z);
		else return Smath::Vector3(vec4.x / vec4.w, vec4.y / vec4.w, vec4.z / vec4.w);
	}

	static Smath::Matrix4 diag4(const real_t value) {
		return Smath::Matrix4(value, 0, 0, 0,
					   0, value, 0, 0,
					   0, 0, value, 0,
					   0, 0, 0, value);
	}

	static Smath::Matrix4 getLookAt(const Smath::Vector3& forward, const Smath::Vector3& up, const Smath::Vector3& pos) {
		//UVN coordinate system
		Smath::Vector3 N(forward);
		Smath::Vector3 V(up);
		Smath::Vector3 U = cross(N, V);	//right

		N.normalize();
		V.normalize();
		U.normalize();

		auto tx = dot(U, pos);
		auto ty = dot(V, pos);
		auto tz = dot(N, pos);

		return Smath::Matrix4(
			U.x, U.y, U.z, -tx,
			V.x, V.y, V.z, -ty,
			N.x, N.y, N.z, -tz,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static Smath::Matrix4 orthographic(real_t l, real_t r, real_t t, real_t b, real_t n, real_t f) {
		real_t r_l = r-l;
		real_t t_b = t-b;
		real_t f_n = f-n;

		return Smath::Matrix4(
			2.0/r_l, 0, 0, -(r+l)/r_l,
			0, 2.0/t_b, 0, -(t+b)/t_b,
			0, 0, 2.0/f_n, -(f+n)/f_n,
			0, 0, 0,				1
		);
	}
	#pragma warning (pop)

	#pragma warning (push)
	#pragma warning (disable : 4244)
	static Smath::Matrix4 perspective(real_t fov, real_t aspect, real_t nearPlane, real_t farPlane) {
		real_t fovDiv2 = math::toRadians(((double)fov) / 2.0);
		real_t x = 1.0 / (tan((double)fovDiv2) * aspect);
		real_t y = 1.0 / (tan(fovDiv2));
		real_t A = -(nearPlane + farPlane) / (nearPlane - farPlane);
		real_t B = 2.0 * ((double)nearPlane * (double)farPlane) / ((double)nearPlane - (double)farPlane);
		return Smath::Matrix4(
			x, 0.0, 0.0, 0.0,
			0.0, y, 0.0, 0.0,
			0.0, 0.0, A, B,
			0.0, 0.0, 1.0, 0.0
		);
	}
	#pragma warning (pop)
}