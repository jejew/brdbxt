// Big_vector_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector2.h"
using namespace std;

int main()
{

	{
		Vector2<double> a = { 3.1, 5.2 };
		Vector2<double> b = { 7.1, 15.2 };
		Vector2<double> res;
		res = a += b;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 3.1, 5.2 };
		Vector2<double> b = { 7.1, 15.2 };
		Vector2<double> res = {  };
		res = b -= a;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 3.1, -5.2 };
		double b = 7.1;
		Vector2<double> res = { };
		res = a *= b;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 6.2, -10.4};
		double b = 7.1;
		Vector2<double> res = { };
		res = a /= b;
		cout << res << endl;
	}

	{
		Vector2<double> c = { 2.0, -3.0};
		double l = length(c);
		double sql = sqlength(c);
		cout << sql << endl;
	}

	{
		Vector2<double> a = { 3.1, 5.2};
		Vector2<double> b = { 7.1, 15.2};
		Vector2<double> res = b - a;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 3.1, 5.2 };
		Vector2<double> b = { 7.1, 15.2 };
		Vector2<double> res = a + b;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 3.1, -5.2};
		double b = 7.1;
		Vector2<double> res = a * b;
		cout << res << endl;
	}

	{
		Vector2<double> a = { 3.1, -5.2 };
		double b = 7.1;
		Vector2<double> res = b * a;
		cout << res;
	}

	{
		Vector2<double> a = { 6.2, -10.4};
		double b = 7.1;
		Vector2<double> res = a / b;
		cout << res << endl;
	}

	std::cin.get();
	
	return 0;
}
