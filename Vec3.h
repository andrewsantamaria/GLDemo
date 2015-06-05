#ifndef VEC3_H
#define VEC3_H

template <class T>
class Vec3
{
public:
	Vec3();
	Vec3(T cX, T cY, T cZ);

	Vec3<T> &operator = (const Vec3<T> &rhs);
	Vec3<T> operator - (const Vec3<T> &rhs) const;
	Vec3<T> operator / (const float rhs) const;
	Vec3<T> operator + (const float rhs) const;
	Vec3<T> operator * (const float rhs) const;
	friend Vec3<T> operator * (const float a, const Vec3<T> &b);

	static T dotProduct(const Vec3<T> &a, const Vec3<T> &b);
	static Vec3<T> crossProduct(const Vec3<T> &a, const Vec3<T> &b);
	static T length(const Vec3<T> &rhs);
	static Vec3<T> normalize(const Vec3<T> &rhs);

	union
	{
		struct
		{
			T x, y, z;
		};
		T v[3];
	};
};

typedef Vec3<float> Vec3f; // basic 3-float vector

template <class T>
Vec3<T>::Vec3() {}

template <class T>
Vec3<T>::Vec3(T cX, T cY, T cZ) :x(cX), y(cY), z(cZ) {}

template <class T>
Vec3<T> &Vec3<T>::operator = (const Vec3<T> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

template <class T>
Vec3<T> Vec3<T>::operator - (const Vec3<T> &rhs) const
{
	return Vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <class T>
Vec3<T> Vec3<T>::operator / (float rhs) const
{
	return Vec3<T>(x / rhs, y / rhs, z / rhs);
}

template <class T>
Vec3<T> Vec3<T>::operator * (const float rhs) const
{
	return Vec3<T>(x * rhs, y * rhs, z * rhs);
}

template <class T>
Vec3<T> Vec3<T>::operator + (const float rhs) const
{
	return Vec3<T>(x + rhs, y + rhs, z + rhs);
}

template <class T>
Vec3<T> operator * (const float a, const Vec3<T> &b)
{
	return Vec3<T>(a * b.x, a * b.y, a * b.z);
}

template <class T>
T Vec3<T>::dotProduct(const Vec3<T> &a, const Vec3<T> &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <class T>
Vec3<T> Vec3<T>::crossProduct(const Vec3<T> &a, const Vec3<T> &b)
{
	return Vec3<T>(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

template <class T>
T Vec3<T>::length(const Vec3<T> &rhs)
{
	return sqrt(dotProduct(rhs, rhs));
}

template <class T>
Vec3<T> Vec3<T>::normalize(const Vec3<T> &rhs)
{
	return rhs / length(rhs);
}

#endif