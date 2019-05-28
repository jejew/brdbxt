#include <iostream>
#include <cmath>
using namespace std;

double sqrt_newton(double num, double x0)
{
  const double tol = 0.000000005;
  double new_guess;

  while (fabs((new_guess-x0)/new_guess) > tol)
    {
       x0 = new_guess;
       new_guess = (x0 + num/x0)/2;
     }
  return new_guess;
}

int main()
{
  std::cout.precision(16);
  cout << sqrt_newton(612, 10);

  return 0;
}
