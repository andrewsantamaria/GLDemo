#ifndef MAT4_H
#define MAT4_H

#include "Vec3.h"

//column major 4x4 matrix

template <class T>
class Mat4
{
public:
	Mat4();
	Mat4(const T *m);

	Mat4<T> &operator = (const Mat4 &rhs);
	Mat4<T> operator * (const Mat4 &rhs) const;
	Mat4<T> transpose() const;

	static Mat4<T> translate(const Vec3<T> &rhs);
	static Mat4<T> perspective(T fovy, T aspect, T zNear, T zFar);
	static Mat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);
	static Mat4<T> identity();

	union
	{
		T mm[4][4];
		T m[16];
	};
};

typedef Mat4<float> Mat4f;

template <class T>
Mat4<T>::Mat4() {}

template <class T>
Mat4<T>::Mat4(const T *m)
{
	this->m[0] = m[0];
	this->m[1] = m[1];
	this->m[2] = m[2];
	this->m[3] = m[3];

	this->m[4] = m[4];
	this->m[5] = m[5];
	this->m[6] = m[6];
	this->m[7] = m[7];

	this->m[8] = m[8];
	this->m[9] = m[9];
	this->m[10] = m[10];
	this->m[11] = m[11];

	this->m[12] = m[12];
	this->m[13] = m[13];
	this->m[14] = m[14];
	this->m[15] = m[15];
}

template <class T>
Mat4<T> &Mat4<T>::operator = (const Mat4 &rhs)
{
	m[0] = rhs.m[0];
	m[1] = rhs.m[1];
	m[2] = rhs.m[2];
	m[3] = rhs.m[3];

	m[4] = rhs.m[4];
	m[5] = rhs.m[5];
	m[6] = rhs.m[6];
	m[7] = rhs.m[7];

	m[8] = rhs.m[8];
	m[9] = rhs.m[9];
	m[10] = rhs.m[10];
	m[11] = rhs.m[11];

	m[12] = rhs.m[12];
	m[13] = rhs.m[13];
	m[14] = rhs.m[14];
	m[15] = rhs.m[15];

	return *this;
}

template <class T>
Mat4<T> Mat4<T>::operator * (const Mat4<T> &rhs) const
{
	/*
	0	4	8	12
	1	5	9	13
	2	6	10	14
	3	7	11	15
	*/
	Mat4<T> mat;

	mat.m[0] = m[0] * rhs.m[0] + m[4] * rhs.m[1] + m[8] * rhs.m[2] + m[12] * rhs.m[3];
	mat.m[1] = m[1] * rhs.m[0] + m[5] * rhs.m[1] + m[9] * rhs.m[2] + m[13] * rhs.m[3];
	mat.m[2] = m[2] * rhs.m[0] + m[6] * rhs.m[1] + m[10] * rhs.m[2] + m[14] * rhs.m[3];
	mat.m[3] = m[3] * rhs.m[0] + m[7] * rhs.m[1] + m[11] * rhs.m[2] + m[15] * rhs.m[3];

	mat.m[4] = m[0] * rhs.m[4] + m[4] * rhs.m[5] + m[8] * rhs.m[6] + m[12] * rhs.m[7];
	mat.m[5] = m[1] * rhs.m[4] + m[5] * rhs.m[5] + m[9] * rhs.m[6] + m[13] * rhs.m[7];
	mat.m[6] = m[2] * rhs.m[4] + m[6] * rhs.m[5] + m[10] * rhs.m[6] + m[14] * rhs.m[7];
	mat.m[7] = m[3] * rhs.m[4] + m[7] * rhs.m[5] + m[11] * rhs.m[6] + m[15] * rhs.m[7];

	mat.m[8] = m[0] * rhs.m[8] + m[4] * rhs.m[9] + m[8] * rhs.m[10] + m[12] * rhs.m[11];
	mat.m[9] = m[1] * rhs.m[8] + m[5] * rhs.m[9] + m[9] * rhs.m[10] + m[13] * rhs.m[11];
	mat.m[10] = m[2] * rhs.m[8] + m[6] * rhs.m[9] + m[10] * rhs.m[10] + m[14] * rhs.m[11];
	mat.m[11] = m[3] * rhs.m[8] + m[7] * rhs.m[9] + m[11] * rhs.m[10] + m[15] * rhs.m[11];

	mat.m[12] = m[0] * rhs.m[12] + m[4] * rhs.m[13] + m[8] * rhs.m[14] + m[12] * rhs.m[15];
	mat.m[13] = m[1] * rhs.m[12] + m[5] * rhs.m[13] + m[9] * rhs.m[14] + m[13] * rhs.m[15];
	mat.m[14] = m[2] * rhs.m[12] + m[6] * rhs.m[13] + m[10] * rhs.m[14] + m[14] * rhs.m[15];
	mat.m[15] = m[3] * rhs.m[12] + m[7] * rhs.m[13] + m[11] * rhs.m[14] + m[15] * rhs.m[15];

	return mat;
}

template <class T>
Mat4<T> Mat4<T>::transpose() const
{
	Mat4<T> mat;

	mat.m[0] = m[0];
	mat.m[1] = m[4];
	mat.m[2] = m[8];
	mat.m[3] = m[12];

	mat.m[4] = m[1];
	mat.m[5] = m[5];
	mat.m[6] = m[9];
	mat.m[7] = m[13];

	mat.m[8] = m[2];
	mat.m[9] = m[6];
	mat.m[10] = m[10];
	mat.m[11] = m[14];

	mat.m[12] = m[3];
	mat.m[13] = m[7];
	mat.m[14] = m[11];
	mat.m[15] = m[15];

	return mat;
}

template <class T>
Mat4<T> Mat4<T>::translate(const Vec3<T> &rhs)
{
	Mat4<T> mat = Mat4<T>::identity();

	mat.m[12] = rhs.x;
	mat.m[13] = rhs.y;
	mat.m[14] = rhs.z;

	return mat;
}

// for setting up a perspective matrix
template <class T>
Mat4<T> Mat4<T>::perspective(T fovy, T aspect, T zNear, T zFar)
{
	if (aspect <= 0.0f)
		aspect = std::numeric_limits<T>::epsilon();

	const T tanHalfFovy = tan(fovy * 0.5f);

	Mat4<T> mat = Mat4<T>::identity();
	mat.mm[0][0] = 1.0f / (aspect * tanHalfFovy);
	mat.mm[1][1] = 1.0f / (tanHalfFovy);
	mat.mm[2][2] = -(zFar + zNear) / (zFar - zNear);
	mat.mm[2][3] = -1.0f;
	mat.mm[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);

	return mat;
}

// ortho matrix creation
template <class T>
Mat4<T>  Mat4<T>::ortho(T left, T right, T bottom, T top, T zNear, T zFar)
{
	Mat4<T> mat = Mat4<T>::identity();

	const T width = right - left;
	const T height = top - bottom;
	const T length = zFar - zNear;

	mat.mm[0][0] = 2.0f / width;
	mat.mm[1][1] = 2.0f / height;
	mat.mm[2][2] = -2.0f / length;
	mat.mm[3][0] = -(right + left) / width;
	mat.mm[3][1] = -(top + bottom) / height;
	mat.mm[3][2] = -(zFar + zNear) / length;

	return mat;
}

template <class T>
Mat4<T> Mat4<T>::identity()
{
	Mat4<T> mat;

	mat.m[0] = 1.0f;
	mat.m[1] = 0.0f;
	mat.m[2] = 0.0f;
	mat.m[3] = 0.0f;

	mat.m[4] = 0.0f;
	mat.m[5] = 1.0f;
	mat.m[6] = 0.0f;
	mat.m[7] = 0.0f;

	mat.m[8] = 0.0f;
	mat.m[9] = 0.0f;
	mat.m[10] = 1.0f;
	mat.m[11] = 0.0f;

	mat.m[12] = 0.0f;
	mat.m[13] = 0.0f;
	mat.m[14] = 0.0f;
	mat.m[15] = 1.0f;

	return mat;
}
#endif