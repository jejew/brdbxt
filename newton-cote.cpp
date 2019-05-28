
#include<iostream> 
#include<cmath>
using namespace std;
  
double y(double x) 
{ 
    return cos(x)*exp(-x*x); 
} 
  
double integrate(int n, double x0, double x1) 
{ 
    double h = (x1-x0)/n; 
  
    double s = y(x0)+y(x1); 
  
    for (int i = 1; i < n; i++) 
        s += 2*y(x0+i*h); 
  
    return (h/2)*s; 
} 
  
int main() 
{
    std::cout <<  integrate(100, -1, 3) << std::endl; 
                  
    return 0; 
} 
