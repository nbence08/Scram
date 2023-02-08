#pragma once
#include "Vector4.hpp"
#include "Preprocess_Definitions.hpp"
#include "Matrix3.hpp"

namespace Smath {

	class Matrix4 {
		//column vectors
		Vector4 matrix[4];

	public:
		Matrix4(
			real_t x1, real_t x2, real_t x3, real_t x4,
			real_t y1 = 0.0f, real_t y2 = 0.0f, real_t y3 = 0.0f, real_t y4 = 0.0f,
			real_t z1 = 0.0f, real_t z2 = 0.0f, real_t z3 = 0.0f, real_t z4 = 0.0f,
			real_t w1 = 0.0f, real_t w2 = 0.0f, real_t w3 = 0.0f, real_t w4 = 0.0f);


		Matrix4(const Matrix3& mat3);

		Matrix4(const real_t diag);

		inline Matrix4() : Matrix4(1.0) {}

		//takes three vectors as column vectors
		Matrix4(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);

		Matrix4 operator*(const Matrix4& other);

		void operator *=(const Matrix4& other);

		Vector4 operator*(const Vector4& vec);

		Vector4& operator[](short index);
	};
}
