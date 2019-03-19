#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <cmath>
using namespace std;



std::array<double, 2> fit (const std::vector<double>& x, const std::vector<double>& y)
 {
    const auto n    = x.size();
    const auto s_x  = std::accumulate(x.begin(), x.end(), 0.0);
    const auto s_y  = std::accumulate(y.begin(), y.end(), 0.0);
    const auto s_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    const auto s_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    const auto a    = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
    const auto b    = (s_y - a*s_x);
    std::array<double, 2> A = {a, b};
    return A;
}

int main() {
    std::vector<double> x{6, 5, 11, 7, 5, 4, 4};
    std::vector<double> y{2, 3, 9, 1, 8, 7, 5};
    std::cout << fit(x,y);
}
