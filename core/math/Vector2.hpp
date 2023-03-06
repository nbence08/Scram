#pragma once
#include "Preprocess_Definitions.hpp"
#include <stdexcept>

#include "core_export.hpp"

namespace ScMath {
	class CORE_EXPORT Vector2 {
	public:
		real_t x, y;

		inline Vector2(real_t x = 0.0f, real_t y = 0.0f) : x(x), y(y) {}

		Vector2 operator-() const;

		Vector2 operator-(const Vector2& other) const;

		void operator-=(const Vector2& other);

		Vector2 operator+(const Vector2& other) const;

		void operator+=(const Vector2& other);

		void operator*=(const Vector2& other);

		Vector2 operator*(const real_t c) const;

		void operator*=(const real_t c);

		Vector2 operator/(const real_t c) const;

		void operator/=(const real_t c);

		real_t dot(const Vector2& other) const;

		Vector2 normalized();

		void normalize();

		real_t length();
	};
}
