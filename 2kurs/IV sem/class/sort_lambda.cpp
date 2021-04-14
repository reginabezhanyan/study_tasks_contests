#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

auto func(int a, int b) -> bool
{
    return a < b;
}

auto func(double a, double b) -> auto
{
    return a < b;
}

auto func(char a, char b)
{
    return a < b;
}

int main(int argc, char *argv[])
{    
    std::vector<int> z;
    bool flag = false;
    
    int x;
    while(std::cin >> x) {
        z.push_back(x);
    }
    
    std::sort(z.begin(), z.end(), [flag](auto x, auto y){
        return __builtin_popcount(x) < __builtin_popcount(y); 
    });
    
    /*std::sort(z.begin(), z.end(), [&flag](auto x, auto y){
        return __builtin_popcount(x) < __builtin_popcount(y); 
    });*/
    
    int res = 1;
    std::for_each(z.begin(), z.end(), [&res](auto x) { res *= x;});
     
    //std::for_each(z.begin(), z.end(), [=](auto x) { res *= x;});
    //std::for_each(z.begin(), z.end(), [&](auto x) { res *= x;}); //все лок переменные переданы по ссылке
    
    std::sort(z.begin(), z.end(), std::greater<int>{});
    
    //auto res = srd::accumulate(z.begin(), z.end(), 1, [](int a, int b) { return a * b;});
    auto res2 = std::accumulate(z.begin(), z.end(), 1, std::multiplies<int>());
    
    for(auto x : z) {
        std::cout << x << std::endl;
    }
    std::cout << res2 << std::endl;
}