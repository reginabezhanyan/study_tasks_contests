#include <iostream>
#include <utility>

class S
{
    int a = 0;
    bool ch = true;
    public:
        S()
        {
            int b = 0;
            if(std::cin >> b) {
                a += b; 
            } 
        }
        
        S(const S&& v) : a(v.a)
        { 
            int b = 0;
            if(std::cin >> b) {
                a += b;
            } else {
                ch = false;
            } 
        }
        
        ~S()
        {
            if(!ch) {
                std::cout << a << std::endl;
            }
        }
        
        operator bool() const
        { 
            return !std::cin.eof();
        }
};  