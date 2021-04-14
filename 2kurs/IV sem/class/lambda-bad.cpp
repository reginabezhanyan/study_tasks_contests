#include <functional>
#include <iostream>

std::function<int (int)>
func(void)
{}

int main()
{
    auto f = func();
    
    int c;
    std::cin >> c;
    
    f(c);
    
    
}