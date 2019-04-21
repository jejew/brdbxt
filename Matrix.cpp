#include "Matrix.h"
#include <iostream>
#include <random>

int main()
{
	auto err = [](auto str) { std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

	{
		Matrix<double> u;
		if (u.size() != 0) { err("default contructor test [size]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		if (A.size() != 3) { err("initializer list constructor test [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("initializer list constructor test [indexing with []]"); }
		if (A(0,0) != 3.1 || A(1,0) != 5.2 || A(2,1) != 9.3 || A(3,1) != 5.4) { err("initializer list constructor test [indexing with ()]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B{ A };
		if (B.size() != 3) { err("copy constructor test [size]"); }
		if (B[0] != 3.1 || B[1] != 5.2 || B[2] != 9.3 || B[3] != 5.4) { err("copy constructor test [elements]"); }
		if (A.size() != 3) { err("copy constructor test [src size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("copy constructor test [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B{ std::move(A) };
		if (A.size() != 0) { err("move constructor test [src size]"); }
		if (B.size() != 3) { err("move constructor test [size]"); }
		if (B[0] != 3.1 || B[1] != 5.2 || B[2] != 9.3 || B[3] != 5.4) { err("move constructor test [elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B;
		B = A;
		if (B.size() != 3) { err("assignment test [size]"); }
		if (B[0] != 3.1 || B[1] != 5.2 || B[2] != 9.3 || B[3] != 5.4) { err("assignment test [elements]"); }
		if (A.size() != 3) { err("assignment test [src size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("assignment test [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		A = A;
		if (A.size() != 3) { err("self assignment test [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("self assignment test [elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B;
		B = std::move(A);
		if (A.size() != 0) { err("assignment test [src size]"); }
		if (B.size() != 3) { err("assignment test [size]"); }
		if (B[0] != 3.1 || B[1] != 5.2 || B[2] != 9.3 || B[3] != 5.4) { err("assignment test [elements]"); }
	}

	{
		Matrix<double> C = { 3.1, 5.2, 9.3, 5.4 };
		C = std::move(C);
		if (C.size() != 3) { err("self assignment test [size]"); }
		if (C[0] != 3.1 || C[1] != 5.2 || C[2] != 9.3 || C[3] != 5.4) { err("self assignment test [elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.6 };
		Matrix<double> ref = { 4.0, 10.0, 2.0, 2.0 };
		Matrix<double> res = B - A;
		if (A.size() != 3) { err("operator- test (l-value, l-value) [src size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("operator- test (l-value, l-value) [src elements]"); }
		if (B.size() != 3) { err("operator- test (l-value, l-value) [src size]"); }
		if (B[0] != 7.1 || B[1] != 15.2 || B[2] != 11.3, B[3] != 3.6) { err("operator- test (l-value, l-value) [src elements]"); }
		if (res.size() != 3) { err("operator- test (l-value, l-value) [size]"); }
		if (std::abs(ref[0] - res[0]) > 1e-15 ||
			std::abs(ref[1] - res[1]) > 1e-15 ||
			std::abs(ref[2] - res[2]) > 1e-15) {
			err("operator- test (l-value, l-value) [elements]");
		}
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.6 };
		Matrix<double> ref = { 4.0, 10.0, 2.0, 2.0 };
		Matrix<double> res = B - A;
		if (A.size() != 3) { err("operator- test (r-value, l-value) [src size]"); }
		if (B.size() != 0) { err("operator- test (r-value, l-value) [src size]"); }
		if (res.size() != 3) { err("operator- test (r-value, l-value) [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("operator- test (r-value, l-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.6 };
		Matrix<double> ref = { 4.0, 10.0, 2.0, 2.0 };
		Matrix<double> res = B - std::move(A);
		if (A.size() != 0) { err("operator- test (l-value, r-value) [src size]"); }
		if (B.size() != 3) { err("operator- test (l-value, r-value) [src size]"); }
		if (res.size() != 3) { err("operator- test (l-value, r-value) [size]"); }
		if (B[0] != 7.1 || B[1] != 15.2 || B[2] != 11.3, B[3] != 3.6) { err("operator- test (l-value, r-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> ref = { 4.0, 10.0, 2.0, 2.0 };
		Matrix<double> res = std::move(B) - std::move(A);
		if (A.size() != 3) { err("operator- test (r-value, r-value) [src size]"); }//this argument was not reused!
		if (B.size() != 0) { err("operator- test (r-value, r-value) [src size]"); }
		if (res.size() != 3) { err("operator- test (r-value, r-value) [size]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> ref = { 10.2, 20.4, 20.6, 8.8 };
		Matrix<double> res = A + B;
		if (A.size() != 3) { err("operator+ test (l-value, l-value) [src size]"); }
		if (A.size() != 3) { err("operator+ test (l-value, l-value) [src size]"); }
		if (res.size() != 3) { err("operator+ test (l-value, l-value) [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("operator+ test (l-value, l-value) [src elements]"); }
		if (B[0] != 7.1 || B[1] != 15.2 || B[2] != 11.3, B[3] != 3.6) { err("operator+ test (l-value, l-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> ref = { 10.2, 20.4, 20.6, 8.8 };
		Matrix<double> res = std::move(A) + B;
		if (A.size() != 0) { err("operator+ test (r-value, l-value) [src size]"); }
		if (B.size() != 3) { err("operator+ test (r-value, l-value) [src size]"); }
		if (res.size() != 3) { err("operator+ test (r-value, l-value) [size]"); }
		if (B[0] != 7.1 || B[1] != 15.2 || B[2] != 11.3, B[3] != 3.6) { err("operator+ test (r-value, l-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> ref = { 10.2, 20.4, 20.6, 8.8 };
		Matrix<double> res = A + std::move(B);
		if (A.size() != 3) { err("operator+ test (l-value, r-value) [src size]"); }
		if (B.size() != 0) { err("operator+ test (l-value, r-value) [src size]"); }
		if (res.size() != 3) { err("operator+ test (l-value, r-value) [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("operator+ test (l-value, r-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> ref = { 10.2, 20.4, 20.6, 8.8 };
		Matrix<double> res = std::move(A) + std::move(B);
		if (A.size() != 0) { err("operator+ test (r-value, r-value) [src size]"); }
		if (B.size() != 3) { err("operator+ test (r-value, r-value) [src size]"); }
		if (res.size() != 3) { err("operator+ test (r-value, r-value) [size]"); }
	}

	{
		Matrix<double> A = { 3.1, 5.2, 9.3, 5.4 };
		Matrix<double> B = { 7.1, 15.2, 11.3, 3.4 };
		Matrix<double> res = A * 2.0;
		if (A.size() != 3) { err("operator* test (l-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator* test (l-value, scalar) [size]"); }
		if (A[0] != 3.1 || A[1] != 5.2 || A[2] != 9.3 || A[3] != 5.4) { err("operator* test (l-value, scalar) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, -5.2,  9.3, 2.2 };
		Matrix<double> ref = { 6.2, -10.4, 18.6, 4.4 };
		Matrix<double> res = std::move(A) * 2.0;
		if (A.size() != 0) { err("operator* test (r-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator* test (r-value, scalar) [size]"); }
	}

	{
		Matrix<double> A = { 3.1, -5.2,  9.3, 2.2 };
		Matrix<double> ref = { 6.2, -10.4, 18.6, 4.4 };
		Matrix<double> res = 2.0 * A;
		if (A.size() != 3) { err("operator* test (scalar, l-value) [src size]"); }
		if (res.size() != 3) { err("operator* test (scalar, l-value) [size]"); }
		if (A[0] != 3.1 || A[1] != -5.2 || A[2] != 9.3, A[3] != 2.2) { err("operator* test (scalar, l-value) [src elements]"); }
	}

	{
		Matrix<double> A = { 3.1, -5.2,  9.3, 2.2 };
		Matrix<double> ref = { 6.2, -10.4, 18.6, 4.4 };
		Matrix<double> res = 2.0 * std::move(A);
		if (A.size() != 0) { err("operator* test (scalar, r-value) [src size]"); }
		if (res.size() != 3) { err("operator* test (scalar, r-value) [size]"); }
	}

	{
		Matrix<double> A = { 6.2, -10.4, 18.6, 4.4 };
		Matrix<double> ref = { 3.1, -5.2,  9.3, 2.2 };
		Matrix<double> res = A / 2.0;
		if (A.size() != 3) { err("operator/ test (l-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator/ test (l-value, scalar) [size]"); }
		if (A[0] != 6.2 || A[1] != -10.4 || A[2] != 18.6 || A[3] != 4.4) { err("operator/ test (l-value, scalar) [src elements]"); }
	}

	{
		Matrix<double> A = { 6.2, -10.4, 18.6, 4.4 };
		Matrix<double> ref = { 3.1, -5.2,  9.3, 2.2 };
		Matrix<double> res = std::move(A) / 2.0;
		if (A.size() != 0) { err("operator/ test (r-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator/ test (r-value, scalar) [size]"); }
	}

	std::cout << "All tests are successful!\n";
	std::cin.get();
	return 0;

}