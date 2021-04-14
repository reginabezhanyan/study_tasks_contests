#include <iostream>

using namespace std;

class A {
    char c;
public:
    virtual int g() = 0;
    virtual int f(int a) {
        cout << "A::f" << endl;
        c += 1;
        return c;
    }
    virtual ~A() = 0;
};

A::~A() {}

class B : public A {
    int b;
public:
    using A::f;
    int f(int a) override final{
        cout << "B::f" << endl;
        b += 1;
        return b;
    }
    int g() override {
        b += f(b); 
        return b;
    }
}; 

int main() {
    A a;
    B b;
    A &pb = b;
    pb.f(1); 
    b.f(1); 
    cout << sizeof(a) << " " << sizeof(b) << endl;
}