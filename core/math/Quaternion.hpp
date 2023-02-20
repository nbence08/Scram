#pragma once
#include "Matrix3.hpp"
#include "Vector3.hpp"

namespace ScMath {
	class Quaternion {

		double r, i, j, k;

	public:
		Quaternion(double r, double i, double j, double k) {
			this->r = r;
			this->i = i;
			this->j = j;
			this->k = k;
		}

		void operator*=(const Quaternion& other) {
			double newr = r * other.r - i * other.i - j * other.j - k * other.k;
			double newi = r * other.i + i * other.r + j + other.k - k * other.j;
			double newj = r * other.j - i * other.k + j * other.r + k * other.i;
			double newk = r * other.k + i * other.j - j * other.i + k * other.r;

			r = newr;
			i = newi;
			j = newj;
			k = newk;
		}

		Quaternion conjugate() { return Quaternion(r, -i, -j, -k); }

		Quaternion& operator*(const Quaternion& other) {
			Quaternion val = *this;
			val *= other;
			return val;
		}

#pragma warning (push)
#pragma warning(disable : 4244)
		//rotation matrix, to be rotated vector should be multiplied from left with this matrix
		ScMath::Matrix3 getRotationMatrix() {
			double iSq = i * i, jSq = j * j, kSq = k * k;
			double s = 2.0f / (r * r + iSq + jSq + kSq);
			double ij = i * j, kr = k * r, ik = i * k, jr = j * r, jk = j * k, ir = i * r;

			return ScMath::Matrix3(1.0 - s * (jSq + kSq), s * (ij - kr), s * (ik + jr),
				s * (ij + kr), 1.0 - s * (iSq + kSq), s * (jk - ir),
				s * (ik - jr), s * (jk + ir), 1.0 - s * (iSq + jSq));
		}
#pragma warning (pop)

		static Quaternion rotation(double arc, double axisX, double axisY, double axisZ) {
			double cosCoeff = cos(arc / 2.0);
			double sinCoeff = sin(arc / 2.0);
			double norm2 = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);

			return Quaternion(cosCoeff, sinCoeff * axisX / norm2, sinCoeff * axisY / norm2, sinCoeff * axisZ / norm2);
		}

		static Quaternion rotation(double arc, ScMath::Vector3 axis) {
			return rotation(arc, (double)axis.x, (double)axis.y, (double)axis.z);
		}
	};
}

