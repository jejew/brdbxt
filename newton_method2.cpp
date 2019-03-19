#include <iostream>
#include <cmath>
using namespace std;

template < typename E, typename F, typename T > T sqrt_newton(E e, F f, T x0, T num)
{
  const double tol = 0.000000005;
  T new_guess;

  new_guess = f((e(x0)/x0));
  while (fabs((new_guess-x0)/new_guess) > tol)
    {
       x0 = new_guess;
       new_guess = f((x0+num/x0));
     }
  return new_guess;
}

int main()
{
  std::cout.precision(16);
  cout << sqrt_newton([](double x){ return x + 612.0; }, [](double x){ return x/2.0; }, 10.0, 612.0);

  return 0;
}

