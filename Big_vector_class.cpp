// Big_vector_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector2.h"

int main()
{
	auto err = [](auto str) { std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

	{
		Vector2<double> a = { 3.1, 5.2, 9.3 };
		Vector2<double> b = { 7.1, 15.2, 11.3 };
		Vector2<double> ref = { 10.2, 20.4, 20.6 };
		a += b;
		if (a.size() != 3) { err("+= test [size]"); }
		if (b.size() != 3) { err("+= test [src size]"); }
		if (b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3) { err("+= test [src elements]"); }
		if (length(a - ref) > 1e-15) { err("+= test [value]"); }

	}

	{
		Vector2<double> a = { 3.1, 5.2, 9.3 };
		Vector2<double> b = { 7.1, 15.2, 11.3 };
		Vector2<double> ref = { 4.0, 10.0, 2.0 };
		b -= a;
		if (a.size() != 3) { err("-= test [size]"); }
		if (b.size() != 3) { err("-= test [src size]"); }
		if (a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3) { err("-= test [src elements]"); }
		if (length(b - ref) > 1e-15) { err("-= test [value]"); }
	}

	{
		Vector2<double> a = { 3.1, -5.2,  9.3 };
		Vector2<double> ref = { 6.2, -10.4, 18.6 };
		a *= 2.0;
		if (a.size() != 3) { err("*= test [size]"); }
		if (length(a - ref) > 1e-15) { err("*= test [value]"); }
	}

	{
		Vector2<double> a = { 6.2, -10.4, 18.6 };
		Vector2<double> ref = { 3.1, -5.2,  9.3 };
		a /= 2.0;
		if (a.size() != 3) { err("/= test [size]"); }
		if (length(a - ref) > 1e-15) { err("/= test [value]"); }
	}

	{
		Vector2<double> c = { 2.0, -3.0, 6.0 };
		double l = length(c);
		double sql = sqlength(c);
		if (std::abs(l - 7.0) > 1e-15) { err("length test [value]"); }
		if (std::abs(sql - 49.0) > 1e-15) { err("sq length test [value]"); }
		if (c.size() != 3) { err("length test [src size]"); }
		if (c[0] != 2.0 || c[1] != -3.0 || c[2] != 6.0) { err("length test [src elements]"); }
	}

	{
			Vector2<double> a = { 3.1, 5.2, 9.3 };
			Vector2<double> b = { 7.1, 15.2, 11.3 };
			Vector2<double> ref = { 4.0, 10.0, 2.0 };
			Vector2<double> res = b - a;
			if (a.size() != 3) { err("operator- test (l-value, l-value) [src size]"); }
			if (a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3) { err("operator- test (l-value, l-value) [src elements]"); }
			if (b.size() != 3) { err("operator- test (l-value, l-value) [src size]"); }
			if (b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3) { err("operator- test (l-value, l-value) [src elements]"); }
			if (res.size() != 3) { err("operator- test (l-value, l-value) [size]"); }
			if (std::abs(ref[0] - res[0]) > 1e-15 ||
				std::abs(ref[1] - res[1]) > 1e-15 ||
				std::abs(ref[2] - res[2]) > 1e-15) {
				err("operator- test (l-value, l-value) [elements]");
			}
	}

	{
		Vector2<double> a = { 3.1, 5.2, 9.3 };
		Vector2<double> b = { 7.1, 15.2, 11.3 };
		Vector2<double> ref = { 10.2, 20.4, 20.6 };
		Vector2<double> res = a + b;
		if (a.size() != 3) { err("operator+ test (l-value, l-value) [src size]"); }
		if (b.size() != 3) { err("operator+ test (l-value, l-value) [src size]"); }
		if (res.size() != 3) { err("operator+ test (l-value, l-value) [size]"); }
		if (a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3) { err("operator+ test (l-value, l-value) [src elements]"); }
		if (b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3) { err("operator+ test (l-value, l-value) [src elements]"); }
		if (length(res - ref) > 1e-15) { err("operator+ test (l-value, l-value) [value]"); }
	}

	{
		Vector2<double> a = { 3.1, -5.2,  9.3 };
		Vector2<double> ref = { 6.2, -10.4, 18.6 };
		Vector2<double> res = a * 2.0;
		if (a.size() != 3) { err("operator* test (l-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator* test (l-value, scalar) [size]"); }
		if (a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3) { err("operator* test (l-value, scalar) [src elements]"); }
		if (length(res - ref) > 1e-15) { err("operator* test (l-value, scalar) [value]"); }
	}

	{
		Vector2<double> a = { 6.2, -10.4, 18.6 };
		Vector2<double> ref = { 3.1, -5.2,  9.3 };
		Vector2<double> res = a / 2.0;
		if (a.size() != 3) { err("operator/ test (l-value, scalar) [src size]"); }
		if (res.size() != 3) { err("operator/ test (l-value, scalar) [size]"); }
		if (a[0] != 6.2 || a[1] != -10.4 || a[2] != 18.6) { err("operator/ test (l-value, scalar) [src elements]"); }
		if (length(res - ref) > 1e-15) { err("operator/ test (l-value, scalar) [value]"); }
	}





	std::cin.get();
}
