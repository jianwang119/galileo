
#include "matrix4.h"

void galileo::matrix4::inverse()
{
	float det = determinant();

	matrix4 inverse;
	inverse.data[0][0] = fdet3(
		data[1][1], data[1][2], data[1][3],
		data[2][1], data[2][2], data[2][3],
		data[3][1], data[3][2], data[3][3]) / det;
	inverse.data[0][1] = -fdet3(
		data[0][1], data[0][2], data[0][3],
		data[2][1], data[2][2], data[2][3],
		data[3][1], data[3][2], data[3][3]) / det;
	inverse.data[0][2] = fdet3(
		data[0][1], data[0][2], data[0][3],
		data[1][1], data[1][2], data[1][3],
		data[3][1], data[3][2], data[3][3]) / det;
	inverse.data[0][3] = -fdet3(
		data[0][1], data[0][2], data[0][3],
		data[1][1], data[1][2], data[1][3],
		data[2][1], data[2][2], data[2][3]) / det;
	inverse.data[1][0] = -fdet3(
		data[1][0], data[1][2], data[1][3],
		data[2][0], data[2][2], data[2][3],
		data[3][0], data[3][2], data[3][3]) / det;
	inverse.data[1][1] = fdet3(
		data[0][0], data[0][2], data[0][3],
		data[2][0], data[2][2], data[2][3],
		data[3][0], data[3][2], data[3][3]) / det;
	inverse.data[1][2] = -fdet3(
		data[0][0], data[0][2], data[0][3],
		data[1][0], data[1][2], data[1][3],
		data[3][0], data[3][2], data[3][3]) / det;
	inverse.data[1][3] = fdet3(
		data[0][0], data[0][2], data[0][3],
		data[1][0], data[1][2], data[1][3],
		data[2][0], data[2][2], data[2][3]) / det;
	inverse.data[2][0] = fdet3(
		data[1][0], data[1][1], data[1][3],
		data[2][0], data[2][1], data[2][3],
		data[3][0], data[3][1], data[3][3]) / det;
	inverse.data[2][1] = -fdet3(
		data[0][0], data[0][1], data[0][3],
		data[2][0], data[2][1], data[2][3],
		data[3][0], data[3][1], data[3][3]) / det;
	inverse.data[2][2] = fdet3(
		data[0][0], data[0][1], data[0][3],
		data[1][0], data[1][1], data[1][3],
		data[3][0], data[3][1], data[3][3]) / det;
	inverse.data[2][3] = -fdet3(
		data[0][0], data[0][1], data[0][3],
		data[1][0], data[1][1], data[1][3],
		data[2][0], data[2][1], data[2][3]) / det;
	inverse.data[3][0] = -fdet3(
		data[1][0], data[1][1], data[1][2],
		data[2][0], data[2][1], data[2][2],
		data[3][0], data[3][1], data[3][2]) / det;
	inverse.data[3][1] = fdet3(
		data[0][0], data[0][1], data[0][2],
		data[2][0], data[2][1], data[2][2],
		data[3][0], data[3][1], data[3][2]) / det;
	inverse.data[3][2] = -fdet3(
		data[0][0], data[0][1], data[0][2],
		data[1][0], data[1][1], data[1][2],
		data[3][0], data[3][1], data[3][2]) / det;
	inverse.data[3][3] = fdet3(
		data[0][0], data[0][1], data[0][2],
		data[1][0], data[1][1], data[1][2],
		data[2][0], data[2][1], data[2][2]) / det;
	*this = inverse;
}

void galileo::matrix4::transpose()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			swap(data[i][j], data[j][i]);
}

float galileo::matrix4::determinant()
{
	float det;
	det = data[0][0] * fdet3(
		data[1][1], data[1][2], data[1][3],
		data[2][1], data[2][2], data[2][3],
		data[3][1], data[3][2], data[3][3]);
	det -= data[0][1] * fdet3(
		data[1][0], data[1][2], data[1][3],
		data[2][0], data[2][2], data[2][3],
		data[3][0], data[3][2], data[3][3]);
	det += data[0][2] * fdet3(
		data[1][0], data[1][1], data[1][3],
		data[2][0], data[2][1], data[2][3],
		data[3][0], data[3][1], data[3][3]);
	det -= data[0][3] * fdet3(
		data[1][0], data[1][1], data[1][2],
		data[2][0], data[2][1], data[2][2],
		data[3][0], data[3][1], data[3][2]);
	return det;
}

galileo::matrix4 galileo::rotate(const vector3 & axis, FLOAT radian)
{
	galileo::matrix4 ret;
	vector3 _axis = galileo::normalize(axis);
	float x = _axis.x();
	float y = _axis.y();
	float z = _axis.z();
	float cosine = cos(radian);
	float sine = sin(radian);
	float t = 1 - cosine;
	ret.data[0][0] = t * x * x + cosine;
	ret.data[0][1] = t * x * y - sine * y;
	ret.data[0][2] = t * x * z + sine * y;
	ret.data[0][3] = 0.0;
	ret.data[1][0] = t * x * y + sine * z;
	ret.data[1][1] = t * y * y + cosine;
	ret.data[1][2] = t * y * z - sine * x;
	ret.data[1][3] = 0.0;
	ret.data[2][0] = t * x * z - sine * y;
	ret.data[2][1] = t * y * z + sine * x;
	ret.data[2][2] = t * z * z + cosine;
	ret.data[2][3] = 0.0;
	ret.data[3][0] = 0.0;
	ret.data[3][1] = 0.0;
	ret.data[3][2] = 0.0;
	ret.data[3][3] = 1.0;
	return ret;
}

galileo::matrix4 galileo::view(const vector3& eye, const vector3& lookat, const vector3& up)
{
	galileo::matrix4 ret = galileo::matrix4::identity();
	vector3 w = -(galileo::normalize(lookat));
	vector3 u = galileo::normalize(cross(up, w));
	vector3 v = cross(w, u);
	ret.data[0][0] = u.x();
	ret.data[0][1] = u.y();
	ret.data[0][2] = u.z();
	ret.data[1][0] = v.x();
	ret.data[1][1] = v.y();
	ret.data[1][2] = v.z();
	ret.data[2][0] = w.x();
	ret.data[2][1] = w.y();
	ret.data[2][2] = w.z();
	galileo::matrix4 move = galileo::matrix4::identity();
	move.data[0][3] = -(eye.x());
	move.data[1][3] = -(eye.y());
	move.data[2][3] = -(eye.z());
	ret = ret * move;
	return ret;
}
