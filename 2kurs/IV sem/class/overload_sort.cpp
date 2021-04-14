#include <algorithm>
#include <iostream>
#include <vector>

struct F
{
    bool operator ()(int a, int b, int c, int d)
    {
        return a + b + c + d < 0;
    }
};

struct Crit
{
    bool dir = false;
    Crit(bool dir = false) : dir(dir) {}
    
    bool operator()(int x, int y)
    {
        if(dir) {
            return __builtin_popcount(x) > __builtin_popcount(y);
        } else {
            return __builtin_popcount(x) < __builtin_popcount(y);
        } 
    }
};

int main()
{
    /*F x;
    
    auto r1 = x(1, 2, 3, 4);
    auto r2 = F()(1, 2, 3, 4);*/
    
    std::vector<int> z;
    
    int x;
    while(std::cin >> x) {
        z.push_back(x);
    }
    
    //[z.begin(), z.end()): <
    //std::sort(z.begin(), z.end());
    std::sort(z.begin(), z.end(), Crit{}); //sort по количеству установленных бит
    
    //std::stable_sort(z.begin(), z.end());
    
    for(auto x : z) {
        std::cout << x << std::endl;
    }
}