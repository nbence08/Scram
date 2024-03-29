#include "Matrix3.hpp"

namespace ScMath {
	Matrix3::Matrix3(real_t x1, real_t x2, real_t x3,
		real_t y1, real_t y2, real_t y3,
		real_t z1, real_t z2, real_t z3) {
		matrix[0] = ScMath::Vector3(x1, y1, z1);
		matrix[1] = ScMath::Vector3(x2, y2, z2);
		matrix[2] = ScMath::Vector3(x3, y3, z3);
	}

	//takes three vectors as column vectors
	Matrix3::Matrix3(ScMath::Vector3 v1, ScMath::Vector3 v2, ScMath::Vector3 v3) {
		matrix[0] = v1;
		matrix[1] = v2;
		matrix[2] = v3;
	}

	Matrix3 Matrix3::operator*(const Matrix3& other) {
		auto ret = *this;
		ret *= other;
		return ret;
	}

	void Matrix3::operator *=(const Matrix3& other) {
		ScMath::Vector3 r1(matrix[0].x, matrix[1].x, matrix[2].x);
		ScMath::Vector3 r2(matrix[0].y, matrix[1].y, matrix[2].y);
		ScMath::Vector3 r3(matrix[0].z, matrix[1].z, matrix[2].z);
		const ScMath::Vector3& c1 = other.matrix[0];
		const ScMath::Vector3& c2 = other.matrix[1];
		const ScMath::Vector3& c3 = other.matrix[2];

		matrix[0].x = dot(r1, c1); matrix[1].x = dot(r1, c2); matrix[2].x = dot(r1, c3);
		matrix[0].y = dot(r2, c1); matrix[1].y = dot(r2, c2); matrix[2].y = dot(r2, c3);
		matrix[0].z = dot(r3, c1); matrix[1].z = dot(r3, c2); matrix[2].z = dot(r3, c3);
	}

	ScMath::Vector3 Matrix3::operator*(const ScMath::Vector3& vec) {
		ScMath::Vector3 r1(matrix[0].x, matrix[1].x, matrix[2].x);
		ScMath::Vector3 r2(matrix[0].y, matrix[1].y, matrix[2].y);
		ScMath::Vector3 r3(matrix[0].z, matrix[1].z, matrix[2].z);

		return ScMath::Vector3(dot(r1, vec), dot(r2, vec), dot(r3, vec));
	}

	ScMath::Vector3& Matrix3::operator[](int index) {
		if (index < 0 || 2 < index) {
			throw std::out_of_range("Index must from [0,2] for Matrix3!");
		}
		else {
			return matrix[index];
		}
	}

	ScMath::Vector3 Matrix3::operator[](int index) const {
		if (index < 0 || 2 < index) {
			throw std::out_of_range("Index must from [0,2] for Matrix3!");
		}
		else {
			return ScMath::Vector3(matrix[index]);
		}
	}
}
