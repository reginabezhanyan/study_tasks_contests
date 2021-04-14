#include <iostream>

std::string gen_power(uint32_t power)
{
    if (!power) {
        return "1";
    }
    std::string ans = "x";
    for (size_t i = 1; i < power; ++i) {
        ans += "x*";
    }
    return ans;
}