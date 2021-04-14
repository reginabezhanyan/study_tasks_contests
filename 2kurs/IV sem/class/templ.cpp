#include <iostream>
#include <functional>
#include <string>
#include <tuple>

using namespace std;

struct A {
    int f(int a) {
        cout << "f" << a << endl;
    }
};

template <typename R>
struct MyApply {
    template<typename F>
}

int g(int a, int b) {
    return 42;
}

int main()
{
    struct big_str = "sss";
    auto f1 = bind(f, cref(big_str), _2, _1);
    f1(2, 40);
    
    auto f2 = bind(func(), "aaa", _1);
    f2(3.);
    
    auto f3 = bind(f, _1, bind(func(), _1, 4), _2);
    f3("ddd", 5);
    
    A b;
    auto f4 = bind(&A::f, &b, 15);
    A a;
    f4();
    
    auto f5 = mem_fn(&A::f);
    f5(a, 16);
    
    auto f6 = bind(apply<int(int, int), std::tuple<int, int>>, _1, std::forward_as_tuple(4, 5));
    cout << f6(g);
    
    auto f7 = bind(MyApply<int>(), _1, 4, 5);
    cout << f7(g);
}