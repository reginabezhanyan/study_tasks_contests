#include <iostream>

class A
{
    int a;
    bool cnt = false;

public: 
    A()
    { 
        std::cin >> a; 
    }
    A(const A& b) 
    {
        std::cin >> a;
        a += b.a;
        cnt = true;
    }
    ~A()
    {
        if(cnt) {
            std::cout << a << std::endl;
        }
    }
    
};