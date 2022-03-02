#include "Matrix4.h"

namespace SMath {
	Matrix4::Matrix4(
		real_t x1, real_t x2, real_t x3, real_t x4,
		real_t y1, real_t y2, real_t y3, real_t y4,
		real_t z1, real_t z2, real_t z3, real_t z4,
		real_t w1, real_t w2, real_t w3, real_t w4) {
		matrix[0] =  SMath::Vector4(x1, y1, z1, w1);
		matrix[1] =  SMath::Vector4(x2, y2, z2, w2);
		matrix[2] =  SMath::Vector4(x3, y3, z3, w3);
		matrix[3] =  SMath::Vector4(x4, y4, z4, w4);
	}

	Matrix4::Matrix4(const SMath::Matrix3& mat) {
		matrix[0] =  SMath::Vector4(mat[0], 0.0);
		matrix[1] =  SMath::Vector4(mat[1], 0.0);
		matrix[2] =  SMath::Vector4(mat[2], 0.0);
		matrix[3] =  SMath::Vector4(0.0, 0.0, 0.0, 1.0);
	}

	Matrix4::Matrix4(const real_t diag) {
		matrix[0] =  SMath::Vector4(diag, 0, 0, 0);
		matrix[1] =  SMath::Vector4(0, diag, 0, 0);
		matrix[2] =  SMath::Vector4(0, 0, diag, 0);
		matrix[3] =  SMath::Vector4(0, 0, 0, diag);
	}

	//takes three vectors as column vectors
	Matrix4::Matrix4( SMath::Vector4 v1,  SMath::Vector4 v2,  SMath::Vector4 v3,  SMath::Vector4 v4) {
		matrix[0] = v1;
		matrix[1] = v2;
		matrix[2] = v3;
		matrix[3] = v4;
	}

	Matrix4 Matrix4::operator*(const Matrix4& other) {
		auto ret = *this;
		ret *= other;
		return ret;
	}

	void Matrix4::operator *=(const Matrix4& other) {
		 SMath::Vector4 r1(matrix[0].x, matrix[1].x, matrix[2].x, matrix[3].x);
		 SMath::Vector4 r2(matrix[0].y, matrix[1].y, matrix[2].y, matrix[3].y);
		 SMath::Vector4 r3(matrix[0].z, matrix[1].z, matrix[2].z, matrix[3].z);
		 SMath::Vector4 r4(matrix[0].w, matrix[1].w, matrix[2].w, matrix[3].w);
		const  SMath::Vector4& c1 = other.matrix[0];
		const  SMath::Vector4& c2 = other.matrix[1];
		const  SMath::Vector4& c3 = other.matrix[2];
		const  SMath::Vector4& c4 = other.matrix[3];

		matrix[0].x = dot(r1, c1); matrix[1].x = dot(r1, c2); matrix[2].x = dot(r1, c3); matrix[3].x = dot(r1, c4);
		matrix[0].y = dot(r2, c1); matrix[1].y = dot(r2, c2); matrix[2].y = dot(r2, c3); matrix[3].y = dot(r2, c4);
		matrix[0].z = dot(r3, c1); matrix[1].z = dot(r3, c2); matrix[2].z = dot(r3, c3); matrix[3].z = dot(r3, c4);
		matrix[0].w = dot(r4, c1); matrix[1].w = dot(r4, c2); matrix[2].w = dot(r4, c3); matrix[3].w = dot(r4, c4);
	}

	 SMath::Vector4 Matrix4::operator*(const  SMath::Vector4& vec) {
		 SMath::Vector4 r1(matrix[0].x, matrix[1].x, matrix[2].x, matrix[3].x);
		 SMath::Vector4 r2(matrix[0].y, matrix[1].y, matrix[2].y, matrix[3].y);
		 SMath::Vector4 r3(matrix[0].z, matrix[1].z, matrix[2].z, matrix[3].z);
		 SMath::Vector4 r4(matrix[0].w, matrix[1].w, matrix[2].w, matrix[3].w);

		return  SMath::Vector4(dot(r1, vec), dot(r2, vec), dot(r3, vec), dot(r4, vec));
	}

	 SMath::Vector4& Matrix4::operator[](short index) {
		if (index < 0 || 3 < index) {
			throw std::out_of_range("Index must be from [0,4] for Matrix4!");
		}
		else {
			return matrix[index];
		}
	}
}