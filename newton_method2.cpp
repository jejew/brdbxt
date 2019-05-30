#include <iostream>
#include <cmath>
using namespace std;


template < typename E, typename F, typename T> T sqrt_newton(E e, F f, T x0)
{
    double x1;
  T new_guess;
    
    for (int i; i < x0; ++i)
    {
        x1 = (x0 - ((e(x0)/f(x0))));
        x0 = x1;
    }
  
  return x1;
  
}

int main()
{
  std::cout.precision(16);
  cout << sqrt_newton([](double x){ return x * x - 612.0; }, [](double x){ return 2.0 * x; }, 10.0);

  return 0;
}

