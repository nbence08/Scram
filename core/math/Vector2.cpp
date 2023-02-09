#include "Vector2.hpp"

#include <cmath>

namespace Smath {
	Vector2 Vector2::operator-() const {
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator-(const Vector2& other) const {
		auto ret = *this;
		ret -= other;
		return ret;
	}

	void Vector2::operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	Vector2 Vector2::operator+(const Vector2& other) const {
		auto ret = *this;
		ret += other;
		return ret;
	}

	void Vector2::operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	void Vector2::operator*=(const Vector2& other) {
		x *= other.x;
		y *= other.y;
	}

	Vector2 Vector2::operator*(const real_t c) const {
		auto ret = *this;
		ret *= c;
		return ret;
	}

	void Vector2::operator*=(const real_t c) {
		x *= c;
		y *= c;
	}

	Vector2 Vector2::operator/(const real_t c) const {
		auto ret = *this;
		ret /= c;
		return ret;
	}

	void Vector2::operator/=(const real_t c) {
		if (c == 0.0f) {
			throw std::runtime_error("Division by zero is undefined");
		}
		real_t reciprocal = 1.0f / c;
		*this *= reciprocal;
	}

	real_t Vector2::dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	Vector2 Vector2::normalized() {
		real_t norm2 = sqrtf(dot(*this));

		return *this / norm2;
	}

	void Vector2::normalize() {
		*this = normalized();
	}

	real_t Vector2::length() {
		return sqrtf(dot(*this));
	}
}
