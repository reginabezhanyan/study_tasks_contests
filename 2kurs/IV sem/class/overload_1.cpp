#include <iostream>
#include <cmath>

using namespace std;

/*void f(int a)
{
    cout << "f(int)" << endl;
}*/

void f(int &&a)
{
    cout << "f(int &&)" << endl;
}

void f(int &a)
{
    cout << "f(int &)" << endl;
}

void f(const int &a)
{
    cout << "f(const int &)" << endl;
}

template<typename F, typename T>
auto g(F &&f, T &&x)
{
    return f(std::forward(x));
}
 
template<typename T>
void gg(T &&x)
{
    cout << "gg(T &&x)" << endl;
    f(std::move(x));
}

template<typename T>
void gg(T &x)
{
    cout << "gg(T &x)" << endl;
    f(x);
}

template<typename T>
void ggg(T &&x)
{
    cout << "ggg(T &&x)" << endl;
    f(std::forward<T>(x));
}

//universal reference

// int & && a -> int & a
//const & && a -> const int & a
//int a ->

int main()
{
    int a = 20;
    const int b = 10;
    int &ra = a;
    const int &cra = a;
    
    //rvalue ссылка (lvalue - для него определено понятие адрес)
    int &&rra = a + 1; //после присваивания ведет себя как lvalue 
    int &&rra1 = 100;
    //int &&rrb = rra;
    rra++;
    
    cout << rra << endl;
    
    //static_cast<typename srd::remove_reference<T>::type&&>(t)
    
    int &&rrb = std::move(a); //по сути преобразует ссылочные типы lv - rv
    cout << a << endl;
    ++rrb;
    cout << a << endl;
    
    /*f(10); //один из 3 вариантов лишний
    f(a);
    f(b);
    f(ra);
    f(cra);
    f(std::move(rrb));
    
    /*auto z = g<double (double)>(sin, 2.0);
    
    auto c = [](auto x) { return sin(x); };
    auto zz = g(c, 2.0);
    cout << zz << endl;
    
    gg<const int &>(10);
    gg(a);
    gg(b);
    gg(ra);
    gg(cra);
    gg(std::move(rrb));
    
    ggg(10);
    ggg(a);
    ggg(b);
    ggg(ra);
    ggg(cra);
    ggg(std::move(rrb));*/
    
  
    
}
