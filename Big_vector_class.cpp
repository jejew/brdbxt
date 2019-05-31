// Big_vector_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector2.h"
using namespace std;

int main()
{
    
    auto err = [](auto str){ std::cout << "Vector.h error in: " << str << "\n"; std::exit(-1); };
    
	{
		Vector2<double> a   = {3.1, 5.2};
		Vector2<double> b   = {7.1, 15.2};
		Vector2<double> ref = {10.2, 20.4};
	    a += b;
		if(b.x != 7.1 || b.y != 15.2)               { err("+= test [src elements]"); }
		if(length(a - ref) > 1e-15)                 { err("+= test [value]");        }
		
	}
	

	{
		Vector2<double> a   = {3.1, 5.2};
		Vector2<double> b   = {7.1, 15.2};
		Vector2<double> ref = {4.0, 10.0};
	    b -= a;
		if(a.x != 3.1 || a.y != 5.2)                { err("-= test [src elements]"); }
		if(length(b - ref) > 1e-15)                 { err("-= test [value]");        }
		
	}

	{
		Vector2<double> a = { 3.1, -5.2 };
		Vector2<double> ref = { 6.2, -10.4 };
        a *= 2.0;
		if(length(a - ref) > 1e-15)                 { err("*= test [value]"); }
	}

	{
		Vector2<double> a = { 6.2, -10.4 };
		Vector2<double> ref = { 3.1, -5.2 };
        a /= 2.0;
		if(length(a - ref) > 1e-15)                 { err("/= test [value]"); }
	}
	
	{
		Vector2<double> c = {2.0, -3.0};
		double l = length(c);
		double sql = sqlength(c);
		if(std::abs(l - 3.60555) > 0.001)           { err("length test [value]");        }
		if(std::abs(sql - 13.0) > 1e-15)            { err("sq length test [value]");     }
		if(c.x != 2.0 || c.y != -3.0)               { err("length test [src elements]"); }
	}

	{
		Vector2<double> a = { 3.1, 5.2};
		Vector2<double> b   = {7.1, 15.2};
		Vector2<double> ref = {4.0, 10.0};
		Vector2<double> res = b - a;
		if(a.x != 3.1 || a.y != 5.2)                { err("operator- test [src elements]"); }
		if(b.x != 7.1 || b.y != 15.2)               { err("operator- test [src elements]"); }
		if(std::abs(ref.x-res.x) > 1e-15 ||
		   std::abs(ref.y-res.y) > 1e-15   )        { err("operator- test [elements]"); }
	}

	{
		Vector2<double> a = { 3.1, 5.2};
		Vector2<double> b   = {7.1, 15.2};
		Vector2<double> ref = {10.2, 20.4};
		Vector2<double> res = b + a;
		if(a.x != 3.1 || a.y != 5.2)                { err("operator+ test [src elements]"); }
		if(b.x != 7.1 || b.y != 15.2)               { err("operator+ test [src elements]"); }
		if(std::abs(ref.x-res.x) > 1e-15 ||
		   std::abs(ref.y-res.y) > 1e-15   )        { err("operator+ test [elements]"); }
	}
	
	{
		Vector2<double> a   = {3.1, -5.2};
		Vector2<double> ref = {6.2, -10.4};
		Vector2<double> res = 2.0 * a;
		if(a.x != 3.1 || a.y != -5.2)               { err("operator* test [src elements]"); }
		if(length(res - ref) > 1e-15)               { err("operator* test [value]");        }
	}

	{
		Vector2<double> a   = {6.2, -10.4};
		Vector2<double> ref = {3.1, -5.2};
		Vector2<double> res = a / 2.0;
		if(a.x != 6.2 || a.y != -10.4)            { err("operator/ test [src elements]"); }
		if(length(res - ref) > 1e-15)               { err("operator/ test [value]");        }
	}
	
	{
		Vector2<double> a = { 3.1, 5.2 };
		Vector2<double> b = { 7.1, 15.2 };
		double ref = 101.05;
		double res = a * b;
		if(a.x != 3.1 || a.y != 5.2)                { err("operator* scalar [src elements]"); }
		if(b.x != 7.1 || b.y != 15.2)               { err("operator* scalar [src elements]"); }
		if(std::abs(res - 101.05) > 0.001)           { err("operator* scalar [value]");        }
	}
	
	return 0;
	
}
