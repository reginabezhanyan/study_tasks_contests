#include <memory>
#include <iostream>
#include <vector>

using namespace std;

// std::unique_ptr<T, Deleter>

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

void g(std::unique_ptr<A> arg)
{
    auto ptr = arg.release();
    ptr->f();
    delete ptr;
}

int main()
{
    //A a; A b(a); -  теперь нельзя преносить (копировать)
    //A b(move(a));
    
    std::unique_ptr<A> p1;
    
    {
        //std::unique_ptr<A> p2{new A};
        auto p2 = std::make_unique<A>();
    }
    
    auto p3 = std::make_unique<A>(10);
    
    cout << bool(p3) << endl;
    auto p4 = move(p3);
    cout << bool(p3) << endl;
    
    p4->f();
    
    p4.get()->f();
    
    //std::unique_ptr<A> p5(p4.get()); - и р4, и р5 имеют указатель, ошибка
    
    p4.reset(new A);
    
    cout << "after" << endl;
    
    vector<std::unique_ptr<A>> v1;
    v1.emplace_back(make_unique<A>(1));
    v1.emplace_back(make_unique<A>(2));
    
    auto v2 = std::move(v1);
    
    cout << "before []" << endl;
    {
        std::unique_ptr<A[]> p5(new A[4]);
        p5[1].f();
        cout << "sizeof []: " << sizeof(p5) << endl;
    }
    cout << "after []" << endl;
    
    //std::unique_ptr<A> p6 = new A;
    g(make_unique<A>());
    
    cout << "sizeof: " << sizeof(p4) << endl;
    
    
}