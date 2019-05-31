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


	Matrix<double> p{ Idx1{}, [](int i) { return i * 2; }, 2 };
	Matrix<double> q{ Idx1{}, [](int i) { return i + 1; }, 2 };

	
	{
		Matrix<double> res = p -= q;
		if (p.size() != 4) { err("-= test [size]"); }
		if (q.size() != 4) { err("-= test [src size]"); }
		if (res[0] != -1 || res[1] != 0 || res [2] != 1 ) { err("-= test [src elements]"); }
	}

	{
		Matrix<double> res = p += q;
		if (p.size() != 4) { err("-= test [size]"); }
		if (q.size() != 4) { err("-= test [src size]"); }
		if (res[0] != 0 || res[1] != 2 || res[2] != 4) { err("+= test [src elements]"); }
	}
	
	{
		Vector<double> ref = {0, 4, 8, 12};
		p *= 2.0;
		if(a.size() != 4)          { err("*= test [size]");  }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
		   std::abs(ref[3]-a[3]) > 1e-15     ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Vector<double> ref = {0, 1, 2, 3};
		p /= 2.0;
		if(a.size() != 4)          { err("*= test [size]");  }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
		   std::abs(ref[3]-a[3]) > 1e-15     ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	
	Matrix<double> u = { 2, 3, 4, 1 };
	Matrix<double> v = { 1, 3, 1, 4 };
 
    	{
		Matrix<double> ref = {3, 6, 5, 5};
		Matrix<double> res = u + v;
		if(u.size() != 4)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(u[0] != 2 || u[1] != 3 || u[2] != 4 || u[3] != 1)  { err("operator+ test (l-value, l-value) [src elements]"); }
		if(v.size() != 4)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator+ test (l-value, l-value) [src elements]"); }
		if(res.size() != 4)                            { err("operator+ test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {3, 6, 5, 5};
		Matrix<double> res = std::move(v) + u;
		if(u.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {3, 6, 5, 5};
		Matrix<double> res = v + std::move(u);
		if(u.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator- test (l-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {3, 6, 5, 5};
		Matrix<double> res = std::move(v) + std::move(u);
		if(u.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	
	{
    		Matrix<double> ref = {-1.0, 0.0, -3.0, 3.0};
		Matrix<double> res = v - u;
		if(u.size() != 4)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(u[0] != 2 || u[1] != 3 || u[2] != 4 || u[3] != 1)  { err("operator- test (l-value, l-value) [src elements]"); }
		if(v.size() != 4)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.size() != 4)                            { err("operator- test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	} 
	
	{
    		Matrix<double> ref = {-1.0, 0.0, -3.0, 3.0};
		Matrix<double> res = std::move(v) - u;
		if(u.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	
	{
    		Matrix<double> ref = {-1.0, 0.0, -3.0, 3.0};
		Matrix<double> res = v - std::move(u);
		if(u.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator- test (l-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
    		Matrix<double> ref = {-1.0, 0.0, -3.0, 3.0};
		Matrix<double> res = std::move(v) - std::move(u);
		if(u.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {4, 6, 8, 1};
		Matrix<double> res = u * 2.0;
		if(u.size()   != 4)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {4, 6, 8, 1};
		Matrix<double> res = std::move(u) * 2.0;
		if(u.size()   != 0)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {4, 6, 8, 1};
		Matrix<double> res = 2.0 * u;
		if(u.size()   != 4)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {4, 6, 8, 1};
		Matrix<double> res = 2.0 * std::move(u);
		if(u.size()   != 0)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {1, 1.5, 2, 0.5};
		Matrix<double> res = u * 2.0;
		if(u.size()   != 4)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {1, 1.5, 2, 0.5};
		Matrix<double> res = std::move(u) * 2.0;
		if(u.size()   != 0)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {2, 9, 4, 4};
		Matrix<double> res = u * v;
		if(u.size()   != 4)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(v.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator- test (l-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {2, 9, 4, 4};
		Matrix<double> res = std::move(u) * v;
		if(u.size()   != 0)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(v[0] != 1 || v[1] != 3 || v[2] != 1 || v[3] != 4){ err("operator- test (l-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {2, 9, 4, 4};
		Matrix<double> res = u * std::move(v);
		if(v.size()   != 0)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(u[0] != 2 || u[1] !=  3 || u[2] !=  4 || u[3] != 1){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
	}
	
	{
		Matrix<double> ref = {2, 9, 4, 4};
		Matrix<double> res = std::move(u) * std::move(v);
		if(u.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(v.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
		   std::abs(ref[3]-res[3]) > 1e-15    ){ err("operator+ test (l-value, l-value) [elements]"); }
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
