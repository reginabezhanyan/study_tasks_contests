#include <iostream>

int f(shared_ptr<int>, shared_ptr<int>) {
    return ;
}

int f() noexcept {
    return 42;
}

class A {
    B b;
    C c;
    a() : b(1), c(2) {}
};

int main() {
    f(make_shared<int>(), make_shared<int>());
    
    std::cout << noexcept(f()) << std::endl;
}