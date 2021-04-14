#include <iostream>
#include <complex>
#include <array>
#include <utility>
#include <vector>
#include <cmath>
#include <limits>

namespace Equations
{
    template <typename T>
    auto quadratic(std::array<T, 3> &v, typename T::value_type EPS = 10e-7) -> std::pair<bool, std::vector<T>>
    {
        T disc{};
        std::vector<T> ans{};
        if (fabs(std::norm(v[2]) - 32 * std::numeric_limits<typename T::value_type>::epsilon()) > EPS) {
            disc = v[1] * v[1] - T(4) * v[0] * v[2];
            T x1 = (- v[1] + std::sqrt(disc)) / T(2) * v[2];
            ans.push_back(x1);
            T x2 = (- v[1] - std::sqrt(disc)) / T(2) * v[2];
            ans.push_back(x2);
            return std::make_pair(true, ans);
        } else if(fabs(std::norm(v[1]) - 32 * std::numeric_limits<typename T::value_type>::epsilon()) > EPS) {
            T x = - v[0] / v[1];
            ans.push_back(x);
            return std::make_pair(true, ans);
        } else if(fabs(std::norm(v[0]) - 32 * std::numeric_limits<typename T::value_type>::epsilon()) > EPS) {
            return std::make_pair(true, ans);
        }
        return std::make_pair(false, ans);
    }
};

