#include <iostream>
#include <cmath>
#include <ostream>
#include <vector>
#include <algorithm>
#include <numeric>

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

	Vector2<T>& operator*=(Vector2<T> const& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2<T>& operator/=(Vector2<T> const& v)
	{
		x /= v.x;
		y /= v.y;
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
Vector2<T> operator*(Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x * b.x, a.y * b.y };
}

template<typename T>
Vector2<T> operator/(Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x / b.x, a.y / b.y };
}

template<typename T>
T sqlength(Vector2<T> const& a)
{
	return std::accumulate(a.x, a.y, static_cast<T>(0), [](T const& acc, T const& x) { return acc + x * x; });
}

template<typename T>
T length(Vector2<T>const& a)
{
	return std::sqrt(sqlength(a));
}

template<typename T>
T dot(Vector2<T>const& a, Vector2<T>const& b)
{
	return std::inner_product(a.x, a.y, b.x, b.y );
}

template<typename T>
std::istream& operator>>(std::istream& s, Vector<T> const& d)
{
	std::string tmp;
	std::getline(s, tmp);
	if (tmp.size() > 0)
	{
		std::stringstream ss(tmp);
		std::getline(ss, tmp, ','); d.i = std::stoi(tmp);
		std::getline(ss, tmp, ','); d.x = std::stod(tmp);
		std::getline(ss, d.s);
	}
	return s;
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Vector<T> const& v)
{
	int n = v.size();
	if (n > 0)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			o << v[i] << "   ";
		}
		o << v[n - 1];
	}
	return o;
}