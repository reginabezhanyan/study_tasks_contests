#include <iostream>

template<int N> struct Fib {
    static constexpr int val = Fib<N-1>::val + Fib<N-2>::val;
};

template<> struct Fib<0> { //начальеые значения
    static constexpr int val = 0;
};

template<> struct Fib<1> {
    static constexpr int val = 1;
};

void print() {
    std::cout << std::endl;
}

template <typename T0, typename ...T>
void print(T0 arg0, T... args) {
    std::cout << arg0;
    print(args...);
}

/*template <class T>
using my_map = map<int, T>;*/

int main()
{
    //my_map<double> m; //map<int, double>
    //std::cout << Fib<8>::val;
    
    print(1, 4.5, "aba");
}