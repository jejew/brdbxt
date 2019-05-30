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
    const auto ms_y = s_y/n;
    const auto ms_x = s_x/n;
    double numerator = 0.0;
    double denominator = 0.0;

    for(int i=0; i<n; ++i){
        numerator += (x[i] - ms_x) * (y[i] - ms_y);
        denominator += (x[i] - ms_x) * (x[i] - ms_x);
    }
    const auto a    = numerator / denominator;
    const auto b    = (ms_y - a*ms_x);
    std::array<double, 2> A = {a, b};
    return A;
}

int main() {
    std::vector<double> x{6, 5, 11, 7};
    std::vector<double> y{2, 3, 9, 1};
    std::array<double, 2> f = fit(x, y);
    cout << f[0] << " , " << f[1] << endl;
    cout << "a = 1.16867, b = -4.72289";
    
}
