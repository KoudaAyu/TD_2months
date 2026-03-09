#include "Math.h"


Matrix4x4 Math::Identity4x4() {
	Matrix4x4 buf;
	buf = { 0 };
	buf.m[0][0] = 1;
	buf.m[1][1] = 1;
	buf.m[2][2] = 1;
	buf.m[3][3] = 1;

	return buf;
}

Matrix4x4 Math::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 buf;

	buf.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	buf.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	buf.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	buf.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	buf.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	buf.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	buf.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	buf.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	buf.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	buf.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	buf.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	buf.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	buf.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	buf.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	buf.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	buf.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return buf;

}

Matrix4x4 Math::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 scaleMatrix = Identity4x4();
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;

	Matrix4x4 rotateX = Identity4x4();
	Matrix4x4 rotateY = Identity4x4();
	Matrix4x4 rotateZ = Identity4x4();

	float cosX = cos(rotate.x), sinX = sin(rotate.x);
	float cosY = cos(rotate.y), sinY = sin(rotate.y);
	float cosZ = cos(rotate.z), sinZ = sin(rotate.z);

	rotateX.m[1][1] = cosX;
	rotateX.m[1][2] = sinX;
	rotateX.m[2][1] = -sinX;
	rotateX.m[2][2] = cosX;

	rotateY.m[0][0] = cosY;
	rotateY.m[0][2] = -sinY;
	rotateY.m[2][0] = sinY;
	rotateY.m[2][2] = cosY;

	rotateZ.m[0][0] = cosZ;
	rotateZ.m[0][1] = sinZ;
	rotateZ.m[1][0] = -sinZ;
	rotateZ.m[1][1] = cosZ;

	Matrix4x4 rotationMatrix = Multiply(Multiply(rotateX, rotateY), rotateZ);

	Matrix4x4 scaleRotateMatrix = Multiply(scaleMatrix, rotationMatrix);

	scaleRotateMatrix.m[3][0] = translate.x;
	scaleRotateMatrix.m[3][1] = translate.y;
	scaleRotateMatrix.m[3][2] = translate.z;

	return scaleRotateMatrix;
}


