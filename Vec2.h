#ifndef VEC2_H
#define VEC2_H

template <class T>
class Vec2
{
public:
	Vec2();
	Vec2(float cX, float cY);

	Vec2<T> &operator = (const Vec2<T> &rhs);

	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
};

typedef Vec2<float> Vec2f; // basic 2-float vector

template <class T>
Vec2<T>::Vec2() {};

template <class T>
Vec2<T>::Vec2(float cX, float cY) :x(cX), y(cY) {}

template <class T>
Vec2<T> &Vec2<T>::operator = (const Vec2<T> &rhs)
{
	x = rhs.x;
	y = rhs.y;

	return *this;
}

#endif