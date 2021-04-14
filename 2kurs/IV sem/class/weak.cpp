#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <unistd.h>

using namespace std;

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
        cout << "f()" << a_ << endl;
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
        ptr = CB{1, 0, in};
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
    std::weak_ptr<A> w1; //не влияет на время жизни объекта в отличие от shared
    std::shared_ptr<A> p0;
    
    {
        std::shared_ptr<A> p1 = std::make_shared<A>(100500);
        
        w1 = p1;
        
        //p0 = w1.lock();
    }
    cout << "after" << endl;
    p0 = w1.lock();
    if (p0) {
        p0->f();
    }
}