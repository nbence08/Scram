#pragma once
#include <cmath>
#include <stdexcept>
#include "Preprocess_Definitions.hpp"
#include "Vector4.hpp"

class Vector4;

class Vector3{
public:
	real_t x, y, z;

	inline Vector3(real_t x=0.0f, real_t y=0.0f, real_t z=0.0f): x(x), y(y), z(z) {}
	Vector3(const Vector4& vec4);

	Vector3 operator-() const;

	Vector3 operator-(const Vector3& other) const;

	void operator-=(const Vector3& other);

	Vector3 operator+(const Vector3& other) const;

	void operator+=(const Vector3& other);

	void operator*=(const Vector3& other);

	Vector3 operator*(const real_t c) const;

	void operator*=(const real_t c);

	Vector3 operator/(const real_t c) const;

	void operator/=(const real_t c);

	real_t dot(const Vector3& other) const;

	Vector3 cross(const Vector3& other) const;

	Vector3 normalized() const;

	void normalize();

	real_t length();
};

static inline real_t dot(const Vector3& left, const Vector3& right) {
	return left.dot(right);
}

static inline Vector3 cross(const Vector3& left, const Vector3& right) {
	return left.cross(right);
}