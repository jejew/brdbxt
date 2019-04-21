#include "Matrix.h"
#include <iostream>
#include <random>
#include <chrono>


using namespace std;

int main()
{
	auto err = [](auto str) { std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

	{
		Matrix<int> a{ Idx1{}, [](int i) { return 100 * i * i + 20 * i + 5; }, 3 };
		if (a.size() != 9) { err("constructor from indexible test [size]"); }
		if (a[0] != 5 || a[1] != 125 || a[2] != 445 || a[3] != 965) { err("constructor from indexible test [elements]"); }
	}

	{
		Matrix<int> b{ Idx2{}, [](int i, int j) { return 100 * i * j + 20 * i + 5; }, 3 };
		if (b.size() != 9) { err("constructor from indexible test [size]"); }
		if (b(0,0) != 5 || b(0,1) != 5 || b(0,2) != 5 || b(1,0) != 25 || b(1,1) != 125 || b(1,2) != 225 || b(2,0) != 45 || b(2,1) != 245 || b(2,2) != 445) { err("constructor from indexible test [elements]"); }
	}

	{
		Matrix<double> u;
		if (u.size() != 0) { err("default contructor test [size]"); }
	}

	Matrix<int> m{ Idx1{}, [](int i) { return 2 * i + 2; }, 3 };

	{
		Matrix<int> b{ m };
		if (m.size() != 9) { err("copy constructor test [size]"); }
		if (b[0] != 2 || b[1] != 4 || b[2] != 6) { err("copy constructor test [elements]"); }
		if (m.size() != 9) { err("copy constructor test [src size]"); }
		if (m[0] != 2 || m[1] != 4 || m[2] != 6) { err("copy constructor test [src elements]"); }
	}

	{
		Matrix<int> b{ std::move(m) };
		if (m.size() != 0) { err("move constructor test [src size]"); }
		if (b.size() != 9) { err("move constructor test [size]"); }
		if (b[0] != 2 || b[1] != 4 || b[2] != 6) { err("move constructor test [elements]"); }
	}


	Matrix<double> u{ Idx1{}, [](int i) { return i * 2; }, 3 };
	Matrix<double> v{ Idx1{}, [](int i) { return i + 1; }, 3 };

	
	{
		Matrix<double> res = u -= v;
		if (u.size() != 9) { err("-= test [size]"); }
		if (v.size() != 9) { err("-= test [src size]"); }
		if (res[0] != -1 || res[1] != 0 || res [2] != 1 ) { err("-= test [src elements]"); }
	}

	{
		Matrix<double> res = v += u;
		if (u.size() != 9) { err("-= test [size]"); }
		if (v.size() != 9) { err("-= test [src size]"); }
		if (res[0] != 0 || res[1] != 2 || res[2] != 4) { err("+= test [src elements]"); }
	}
	
	{
		Matrix<double> res = u*= 2.0;
		if (res.size() != 9) { err("*= test [size]"); }
	}


	{
		Matrix<double> res = u /= 2.0;
		if (res.size() != 9) { err("*= test [size]"); }
	}

	{
		Matrix<double> res = u / 2.0;
		if (u.size() != 9) { err("operator/ test (l-value, scalar) [src size]"); }
		if (res.size() != 9) { err("operator/ test (l-value, scalar) [size]"); }
		if (res[1] != 0) { err("operator/ test (l-value, scalar) [src elements]"); }
	}

	{
		Matrix<double> res = u / 2.0;
		if (res.size() != 9) { err("operator/ test (l-value, scalar) [size]"); }
		if (res[1] != 0) { err("operator/ test (l-value, scalar) [src elements]"); }
	}

	{
		Matrix<double> res = u * 2.0;
		if (u.size() != 9) { err("operator/ test (l-value, scalar) [src size]"); }
		if (res.size() != 9) { err("operator/ test (l-value, scalar) [size]"); }
		if (res[1] != 0) { err("operator/ test (l-value, scalar) [src elements]"); }
	}

	{
		Matrix<double> res = 2.0 * u;
		if (u.size() != 9) { err("operator* test (scalar, l-value) [src size]"); }
		if (res.size() != 9) { err("operator* test (scalar, l-value) [size]"); }
		if (res[1] != 0) { err("operator* test (scalar, l-value) [src elements]"); }
	}

	
	{
		Matrix<double> res = u + v;
		if (u.size() != 9) { err("operator+ test (l-value, l-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (l-value, l-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (l-value, l-value) [size]"); }
	}

	
	{
		Matrix<double> res = move(u) + v;
		if (u.size() != 9) { err("operator+ test (r-value, l-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (r-value, l-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (r-value, l-value) [size]"); }
	}

	
	{
		Matrix<double> res = u + move(v);
		if (u.size() != 9) { err("operator+ test (l-value, r-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (l-value, r-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (l-value, r-value) [size]"); }
	}
	

	{
		Matrix<double> res = move(u) + move(v);
		if (u.size() != 9) { err("operator+ test (r-value, r-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (r-value, r-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (r-value, r-value) [size]"); }
	}

	
	{
		Matrix<double> res = u + v;
		if (u.size() != 9) { err("operator+ test (l-value, l-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (l-value, l-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (l-value, l-value) [size]"); }
	}


	{
		Matrix<double> res = move(u) + v;
		if (u.size() != 9) { err("operator+ test (r-value, l-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (r-value, l-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (r-value, l-value) [size]"); }
	}

	
	{
		Matrix<double> res = u + move(v);
		if (u.size() != 9) { err("operator+ test (l-value, r-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (l-value, r-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (l-value, r-value) [size]"); }
	}
	

	{
		Matrix<double> res = move(u) + move(v);
		if (u.size() != 9) { err("operator+ test (r-value, r-value) [src size]"); }
		if (v.size() != 9) { err("operator+ test (r-value, r-value) [src size]"); }
		if (res.size() != 9) { err("operator+ test (r-value, r-value) [size]"); }
	}
	
	std::mt19937 gen(42);
	std::mt19937 gend(43);
	std::normal_distribution<double> distr(100, 20);

	auto t0 = std::chrono::high_resolution_clock::now();

	Matrix<double> data{ Idx1{}, [&](int i) { return distr(gen) + i; }, 3 };
	Matrix<double> ddata{ Idx1{}, [&](int i) { return distr(gend) + i; }, 3 };

	auto t1 = std::chrono::high_resolution_clock::now();

	Matrix<double> mul = data * ddata;

	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << "Allocation took: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " milliseconds." << std::endl;
	std::cout << "Multipication: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " milliseconds." << std::endl;





	cout << u;
	std::cout << "All tests are successful!\n";
	std::cin.get();
	return 0;

}