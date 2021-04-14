#include <iostream>
#include <string>

struct MyException 
{
    std::string str;
    public:
        MyException(std::string str_) : str(str_) {}
        ~MyException()
        {
            std::cout << str << std::endl;
        }
};

void f(std::string str)
{
    if(str == "\0") {
        throw -1;
    }
    MyException exp(str);
    std::string nstr;
    std::cin >> nstr;
    f(nstr);
}

int main()
{
    try {
        std::string str;
        std::cin >> str;
        f(str);
    } catch (...) {   
    }
}