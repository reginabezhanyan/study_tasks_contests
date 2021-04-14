#include <algorithm>
#include <iostream> 

struct S
{
    bool val = false;
    
    void sort(std::vector<int> z)
    {
        std::sort(z.begin(), z.end(), [this](auto a, auto b){
            if(val) return a < b; else return a > b;   
        });
    }
};

int main()
{
    int res, a;
    std::cin >> a;
    
    auto f = [&res, a](int b) {
        res = a + b;
    };
    std::cout << sizeof(f) << std::endl;
    
    struct MyLambda
    {
        int &res;
        int a;
        
        MyLambda(int &res, int a) : res(res), a(a) {}
        
        auto operator()(int b) {
            res = a + b;
        }
    };
    
    auto ff = MyLambda{res, a};
     std::cout << sizeof(ff) << std::endl;
    
    int c;
    std::cin >> c;
    
    f(c);
    std::cout << res << std::endl;
    
    ff(c);
    std::cout << res << std::endl;
}