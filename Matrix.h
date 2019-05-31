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
	int N;
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
	    N = n;
		data.resize(N * N);
		for (int i = 0; i < N * N; ++i) { data[i] = f(i); }
	}

	template<typename F>
	Matrix(Idx2, F f, int n)
	{
	    N = n;
		data.resize(N * N);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				data[N * i + j] = f(i, j);
			}
		}
	}
	
	Matrix( std::initializer_list<T> const& il ) : data{il}{}

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
		return N;
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
Matrix<T> operator/( Matrix<T> const& v1, T const& scl )
{
    Matrix<T> result;
    result.data.resize(v1.data.size());
    std::transform(v1.data.begin(),
    v1.data.end(),
    result.data.begin(),
    [=](T const& x){ return x / scl; });
    return result;
}

template<typename T>
Matrix<T> operator/( Matrix<T> && v1, T const& scl )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v1.data.begin(),
    [=](T const& x){ return x / scl; });
    return std::move(v1);
}

template<typename T>
Matrix<T> operator*( Matrix<T> const& v1, T const& scl )
{
    Matrix<T> result;
    result.data.resize(v1.data.size());
    std::transform(v1.data.begin(),
    v1.data.end(),
    result.data.begin(),
    [=](T const& x){ return x * scl; });
    return result;
}

template<typename T>
Matrix<T> operator*( Matrix<T> && v1, T const& scl )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v1.data.begin(),
    [=](T const& x){ return x * scl; });
    return std::move(v1);
}

template<typename T>
Matrix<T> operator*( T const& scl , Matrix<T> const& v1 )
{
    Matrix<T> result;
    result.data.resize(v1.data.size());
    std::transform(v1.data.begin(),
    v1.data.end(),
    result.data.begin(),
    [=](T const& x){ return scl * x; });
    return result;
}

template<typename T>
Matrix<T> operator*( T const& scl, Matrix<T> && v1 )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v1.data.begin(),
    [=](T const& x){ return scl * x; });
    return std::move(v1);
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> const& B)
{
	int n = A.size();
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < n; ++k) { sum += A(i, k) * B(k, j); }
			return sum;
		}, n);
}

template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> && B)
{
	int n = A.size();
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < n; ++k) { sum += std::move(A(i, k)) * std::move(B(k, j)); }
			return sum;
		}, n);
}

template<typename T>
Matrix<T> operator*(Matrix<T> && A, Matrix<T> const& B)
{
	int n = A.size();
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < n; ++k) { sum += std::move(A(i, k)) * B(k, j); }
			return sum;
		}, n);
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> && B)
{
	int n = A.size();
	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < n; ++k) { sum += (i, k) * std::move(B(k, j)); }
			return sum;
		}, n);
}

template<typename T>
Matrix<T> operator+( Matrix<T> const& v1, Matrix<T> const& v2 )
{
    Matrix<T> result;
    result.data.resize(v1.data.size());
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    result.data.begin(),
    [](T const& x, T const& y){ return x+y; });
    return result;
}
 
 
template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T> const& v2 )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v1.data.begin(),
    [](T const& x, T const& y){ return x+y; }
    );
    return std::move(v1);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T> const& v1, Matrix<T> && v2 )
{
    std::transform(v2.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v2.data.begin(),
    [](T const& x, T const& y){ return x+y; }
    );
    return std::move(v2);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T> && v2 )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v1.data.begin(),
    [](T const& x, T const& y){ return x+y; }
    );
    return std::move(v1);
}

template<typename T>
Matrix<T> operator-( Matrix<T> const& v1, Matrix<T> const& v2 )
{
    Matrix<T> result;
    result.data.resize(v1.data.size());
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    result.data.begin(),
    [](T const& x, T const& y){ return x-y; });
    return result;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T> const& v2 )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v1.data.begin(),
    [](T const& x, T const& y){ return x-y; }
    );
    return std::move(v1);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T> const& v1, Matrix<T> && v2 )
{
    std::transform(v2.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v2.data.begin(),
    [](T const& x, T const& y){ return x-y; }
    );
    return std::move(v2);
}


template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T> && v2 )
{
    std::transform(v1.data.begin(),
    v1.data.end(),
    v2.data.begin(),
    v1.data.begin(),
    [](T const& x, T const& y){ return x-y; }
    );
    return std::move(v1);
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
