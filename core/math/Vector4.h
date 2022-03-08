#pragma once
#include <stdexcept>
#include "core/Preprocess_Definitions.h"
#include "Vector3.h"

namespace SMath {
	class Vector3;
	class Vector4{
	public:
		real_t x, y, z, w;
		inline  Vector4(real_t x = 0.0f, real_t y = 0.0f, real_t z = 0.0f, real_t w = 1.0f) : x(x), y(y), z(z), w(w) {}
		 Vector4(const Vector3& vec3, const real_t w);

		 Vector4 operator-() const;

		 Vector4 operator-(const  Vector4& other) const;

		void operator-=(const  Vector4& other);

		 Vector4 operator+(const  Vector4& other) const;

		void operator+=(const  Vector4& other);

		void operator*=(const  Vector4& other);

		 Vector4 operator*(const real_t c) const;

		void operator*=(const real_t c);

		 Vector4 operator/(const real_t c) const;

		void operator/=(const real_t c);

		real_t dot(const  Vector4& other) const;

		 Vector4 cross(const  Vector4& other) const;

		 Vector4 normalized() const;

		void normalize();

		real_t length();
	};

	static inline real_t dot(const  Vector4& left, const  Vector4& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}
}