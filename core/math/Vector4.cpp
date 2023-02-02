#include "Vector4.hpp"

Vector4 Vector4::operator-() const {
	return Vector4(-x, -y, -z, -w);
}

Vector4::Vector4(const Vector3& vec3, const real_t w) : w(w) {
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
}

Vector4 Vector4::operator-(const Vector4& other) const {
	auto ret = *this;
	ret -= other;
	return ret;
}

void Vector4::operator-=(const Vector4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
}

Vector4 Vector4::operator+(const Vector4& other) const {
	auto ret = *this;
	ret += other;
	return ret;
}

void Vector4::operator+=(const Vector4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
}

void Vector4::operator*=(const Vector4& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
}

Vector4 Vector4::operator*(const real_t c) const {
	auto ret = *this;
	ret *= c;
	return ret;
}

void Vector4::operator*=(const real_t c) {
	x *= c;
	y *= c;
	z *= c;
	w *= c;
}

Vector4 Vector4::operator/(const real_t c) const {
	auto ret = *this;
	ret /= c;
	return ret;
}

void Vector4::operator/=(const real_t c) {
	if (c == 0.0f) {
		throw std::runtime_error("Division by zero is undefined");
	}
	real_t reciprocal = 1.0f / c;
	*this *= reciprocal;
}

real_t Vector4::dot(const Vector4& other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

// only calculates cross product of the first three elements
Vector4 Vector4::cross(const Vector4& other) const {
	return Vector4(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector4 Vector4::normalized() const {
	real_t norm2 = sqrtf(dot(*this));

	return *this / norm2;
}

void Vector4::normalize() {
	*this = normalized();
}

real_t Vector4::length() {
	return sqrtf(dot(*this));
}