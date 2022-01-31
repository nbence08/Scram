#include "Vector3.h"

Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
	auto ret = *this;
	ret -= other;
	return ret;
}

void Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vector3 Vector3::operator+(const Vector3& other) const {
	auto ret = *this;
	ret += other;
	return ret;
}

void Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator*=(const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

Vector3 Vector3::operator*(const real_t c) const {
	auto ret = *this;
	ret *= c;
	return ret;
}

void Vector3::operator*=(const real_t c) {
	x *= c;
	y *= c;
	z *= c;
}

Vector3 Vector3::operator/(const real_t c) const {
	auto ret = *this;
	ret /= c;
	return ret;
}

void Vector3::operator/=(const real_t c) {
	if (c == 0.0f) {
		throw std::runtime_error("Division by zero is undefined");
	}
	real_t reciprocal = 1.0f / c;
	*this *= reciprocal;
}

real_t Vector3::dot(const Vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
	return Vector3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector3 Vector3::normalized() const {
	real_t norm2 = sqrtf(dot(*this));

	return *this / norm2;
}

void Vector3::normalize() {
	*this = normalized();
}

real_t Vector3::length() {
	return sqrtf(dot(*this));
}

Vector3::Vector3(const Vector4& vec4) {
	x = vec4.x;
	y = vec4.y;
	z = vec4.z;
}
