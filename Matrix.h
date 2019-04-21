#include <iostream>
#include <vector>
#include <fstream>

struct Idx1{};
struct Idx2{};

template<typename T>
struct Matrix
{
	int N;
	std::vector<T> data;

	template<typename F>
	Matrix(Idx1, F f, int N)
	{
		data.resize(N);
		for (int i = 0; i < N; ++i) { data[i] = f(i); }
	}

	template<typename F>
	Matrix(Idx2, F f, int N)
	{
		data.resize(N);
			for (int i = 0; i < N; ++i)
			{
			for (int j = 0; j < N; ++j) { data[i] = f(i); }
		}
	}

	T& operator[](int i) { return data[N * i]; };
	T const& operator[](int i) const { return data[N * i]; };

	T& operator()(int i, int j) { return data[N * i + j]; }
	T const& operator()(int i, int j) const { return data[N * i + j]; }


	Matrix() = default;
	Matrix(Matrix const&) = default;
	Matrix(Matrix&&) = default;

	Matrix<T>& operator=(Matrix<T> const& cpy)
	{
		if (&cpy == this) { return*this; }
		data = cpy.data;
		return*this;
	}

	Matrix<T>& operator=(Matrix<T>&& mv)
	{
		if (&mv == this) { return*this; }
		data = std::move(mv.data);
		return*this;
	}

	int size()const
	{
		return static_cast<int>(data.size());
	}

	int row()const
	{
		return static_cast<int>(data.size() / N);
	}

	Matrix(std::initializer_list<T> const& il) : data{ il } {}

};

template<typename T>
Matrix<T> operator/(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] / s; },
		A.size());
}

template<typename T>
Matrix<T>&& operator/(Matrix<T>&& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] / s; },
		A.size());
}

template<typename T>
Matrix<T> operator+(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] + s; },
		A.size());
}

template<typename T>
Matrix<T>&& operator+(Matrix<T>&& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] + s; },
		A.size());
}

template<typename T>
Matrix<T> operator-(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] - s; },
		A.size());
}

template<typename T>
Matrix<T>&& operator-(Matrix<T>&& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] - s; },
		A.size());
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, T const& s)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] * s; },
		A.size());
}

template<typename T>
Matrix<T> operator*(T const& s, Matrix<T> const& A)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] * s; },
		A.size());
}

template<typename T>
Matrix<T> operator*(T const& s, Matrix<T>&& A)
{
	return Matrix<T>(Idx1{},
		[&](auto i) { return A[i] * s; },
		A.size());
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) * mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator*(Matrix<T>&& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) * mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator*(Matrix<T> const& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) * mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator*(Matrix<T>&& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) * mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T> operator+(Matrix<T> const& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) + mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator+(Matrix<T>&& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) + mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator+(Matrix<T> const& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) + mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator+(Matrix<T>&& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) + mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator-(Matrix<T>&& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) - mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator-(Matrix<T> const& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) - mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T>&& operator-(Matrix<T>&& A, Matrix<T>&& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) - mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
Matrix<T> operator-(Matrix<T> const& A, Matrix<T> const& B)
{
	auto N = A.size();

	return Matrix<T>(Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for (int k = 0; k < N; ++k) { sum += mat1(i, k) - mat2(k, j); }
			return sum;
		}, N);
}

template<typename T>
std::istream& operator>>(std::istream& s, Matrix<T> const& d)
{ 
	std::string tmp;
	std::getline(s, tmp);
	if ( tmp.size() > 0 ) 
	{
		std::stringstream ss(tmp);
		std::getline( ss, tmp, ',' ); d.i  = std::stoi(tmp);
		std::getline(ss, tmp, ','); d.x = std::stod(tmp);
		std::getline(ss, d.s);
	}
	return s;
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Matrix<T> const& A)
{
	int n = A.size();
	if (n > 0)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				o << A[i] << "   ";

			}
			o << A[n];
		}
	}
	return o;
}