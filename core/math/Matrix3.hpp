#pragma once
#include "Vector3.hpp"
#include "Preprocess_Definitions.hpp"

namespace ScMath {
	//type traits could be introduced to check whether type is a number
	class Matrix3 {
		//column vectors
		Vector3 matrix[3];

	public:
		Matrix3(real_t x1, real_t x2, real_t x3,
			real_t y1, real_t y2, real_t y3,
			real_t z1, real_t z2, real_t z3);

		//takes three vectors as column vectors
		Matrix3(Vector3 v1, Vector3 v2, Vector3 v3);

		Vector3& operator[](int index);

		/// <summary>
		/// Returns the appropriate column vector of the matrix
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		Vector3 operator[](int index) const;

		Matrix3 operator*(const Matrix3& other);

		void operator *=(const Matrix3& other);

		Vector3 operator*(const Vector3& vec);
	};
}
