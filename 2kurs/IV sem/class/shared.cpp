#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <unistd.h>

using namespace std;

//отличается способ владения памятью

struct A
{
    int a_;
    
    A()
    {
        cout << "A()" << endl;
    }
    A(int a) : a_(a)
    {
        cout << "A(int)" << endl;
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
    
    A(const A&) = delete;
    A(A&&) = delete;
    
    void f()
    {
        cout << "f()" << endl;
    }
};

template<typename T>
class myshared
{
    struct CB
    {
        size_t cnt{};
        T *ptr{};
    };
    
    CB *ptr{};
    
public:
    myshared() = default;
    explicit myshared(A *in)
    {
        ptr = CB{1, in};
    }
    
    ~myshared()
    {
        if(!--ptr->cnt) {
            delete ptr->ptr;
            delete ptr;
        }
    }
    myshared(const myshared &other)
    {
        ptr = other.ptr;
        ++ptr->cnt;
    }
};

int main()
{
    std::shared_ptr<A> p1;
    
    std::shared_ptr<A> p2(new A(2));
    auto p3 = std::make_shared<A>(4);
    
    auto p4 = p3;
}