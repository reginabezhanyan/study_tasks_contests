#include <iostream>
#include <complex>
#include <utility>
#include <array>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

namespace Equations
{
    template<typename T>
    std::pair<bool, std::vector<std::complex<T>>> quadratic(std::array<std::complex<T>, 3> &v)
    {
        T EPS = T(32) * std::numeric_limits<T>::epsilon();
        std::pair<bool, std::vector<std::complex<T>>> ans;
        ans.first = true;
        if(std::norm(v[2]) < EPS) {
            if(std::norm(v[1]) < EPS) {
                if (std::norm(v[0]) < EPS) {
                    ans.first = false; 
                }
            } else {
                ans.second.push_back(- v[0] / v[1]); 
            }
        } else {
            auto D = v[1] * v[1] - std::complex<T>(4) * v[0] * v[2]; 
            ans.second.push_back( (- v[1] - std::sqrt(D)) / (std::complex<T>(2) * v[2]));
            ans.second.push_back( (- v[1] + std::sqrt(D)) / (std::complex<T>(2) * v[2]));
        } 
        return ans;
    }  
}

int main()
{
    std::array<std::complex<double>, 3> v1{
        std::complex<double>(1.0, 2.0),
        std::complex<double>(2.0, 0),
        std::complex<double>(3, 1.3)
    };

    auto res = Equations::quadratic(v1);
    std::cout << res.first << std::endl;
    std::copy(res.second.begin(), res.second.end(), std::ostream_iterator<std::complex<double>>(std::cout, " "));
    std::cout << std::endl;
}