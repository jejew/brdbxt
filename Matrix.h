#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <ostream>


namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_vector1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

inline auto add = [](auto const& x, auto const& y) { return x + y; };
inline auto sub = [](auto const& x, auto const& y) { return x - y; };


struct Idx1 {};
struct Idx2 {};

template<typename T>
struct Matrix
{
	int N = 3;
	std::vector<T> data;

	T& operator()(int i, int j) { return data[N * i + j]; }
	T const& operator()(int i, int j) const { return data[N * i + j]; }

	T& operator[](int i) { return data[i]; }
	T const& operator[](int i) const { return data[i]; }

	Matrix() = default;
	Matrix(Matrix const&) = default;
	Matrix(Matrix&&) = default;

	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix&&) = default;

	template<typename F>
	Matrix(Idx1, F f, int n)
	{
		data.resize(n * N);
		for (int i = 0; i < n * N; ++i) { data[i] = f(i); }
	}

	template<typename F>
	Matrix(Idx2, F f, int n)
	{
		data.resize(n * N);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				data[n * i + j] = f(i, j);
			}
		}
	}

	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_vector2(*this, cpy, *this, add);
		return *this;
	}

	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_vector2(*this, cpy, *this, sub);
		return *this;
	}

	Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_vector1(*this, *this, [=](T const& x) { return x * scl; });
		return *this;
	}

	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_vector1(*this, *this, [=](T const& x) { return x / scl; });
		return *this;
	}

	int size()const
	{
		return static_cast<int>(data.size());
	}

	int row_col() const
	{
		return static_cast<int>(N);
	}

	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}

};

template<typename T>
Matrix<T>&& operator/(Matrix<T>&& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return move(A[i]) / s; },
		3);
}

template<typename T>
Matrix<T> operator/(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] / s; },
		3);
}

template<typename T>
Matrix<T>&& operator*(Matrix<T>&& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] * s; },
		3);
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] * s; },
		3);
}

template<typename T>
Matrix<T>&& operator*(T const& s, Matrix<T>&& A)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return s * A[i]; },
		3);
}

template<typename T>
Matrix<T> operator*(T const& s, Matrix<T> const& A)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return  s * A[i]; },
		3);
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) * B(k, j); }
			return sum;
		}, 3);
}

template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> && B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) * B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator+(Matrix<T> const& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) + B(k, j); }
			return sum;
		}, 3);
}

template<typename T>
Matrix<T> operator+(Matrix<T>&& A, Matrix<T>&& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) + B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator+(Matrix<T> const& A, Matrix<T>&& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) + B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator+(Matrix<T>&& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) + B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator-(Matrix<T> const& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) - B(k, j); }
			return sum;
		}, 3);
}

template<typename T>
Matrix<T> operator-(Matrix<T>&& A, Matrix<T>&& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) - B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator-(Matrix<T>&& A, Matrix<T> const& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) - B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
Matrix<T> operator-(Matrix<T> const& A, Matrix<T>&& B)
{
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < 3; ++k) { sum += A(i, k) - B(k, j); }
			return move(sum);
		}, 3);
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Matrix<T> const& v)
{
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				o << v(i, j) << "   ";;
			}
			cout << endl;
		}
	}
	return o;
}


