#include <iostream>
#include <cmath>
#include <ostream>
#include <vector>
#include <algorithm>


template<typename T>
struct Vector2 
{
	T x, y;

	Vector2<T>& operator+=( Vector2<T> const& v) 
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2<T>& operator-=(Vector2<T> const& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2<T>& operator*=(T const& a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	Vector2<T>& operator/=(T const& a)
	{
		x /= a;
		y /= a;
		return *this;
	}

};

template<typename T>
Vector2<T> operator+(Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x + b.x, a.y + b.y };
}

template<typename T>
Vector2<T> operator-(Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x - b.x, a.y - b.y };
}

template<typename T>
Vector2<T> operator*(Vector2<T> const& v, T const& a)
{
	return Vector2<T>{ v.x * a, v.y * a };
}

template<typename T>
Vector2<T> operator*(T const& a, Vector2<T> const& v)
{
	return Vector2<T>{ a * v.x, a * v.y };
}

template<typename T>
T operator*(Vector2<T> const& u, Vector2<T> const& v)
{
	return u.x * v.x + u.y * v.y;;
}

template<typename T>
Vector2<T> operator/(Vector2<T> const& v, T const& a)
{
	return Vector2<T>{ v.x / a, v.y / a };
}

template<typename T>
T sqlength(Vector2<T> const& a)
{
	return a.x * a.x + a.y * a.y;;
}

template<typename T>
T length(Vector2<T>const& a)
{
	return std::sqrt(sqlength(a));
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Vector2<T> const& v)
{
	o << v.x << " " << v.y;
	return o;
}
