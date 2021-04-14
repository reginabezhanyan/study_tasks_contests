#include <iostream>
#include <cmath>

using namespace std;

void f(int a)
{
    cout << "f()" << endl;
}

void f(int a)
{
    cout << "f(a)" << endl;
}

void f(int a, int &&b)
{
    cout << "f(int, int &&)" << endl;
}

void f(int a, int &b)
{
    cout << "f(int, int &)" << endl;
}

void f(int a, const int &b)
{
    cout << "f(int, const int &)" << endl;
}

void f(int a, int b)
{
    cout << "f(a, b)" << endl;
}

template<typename ...T>
void g(T && ...x)
{
    f(std::forward<T>(x)...);
}

int main()
{
    g();
    g(10);
    g(10, 10);
    
    g(10, 1.5);
    
    int a;
    int &b = a;
    const int &c = a;
    int && d = std::move(a);
    
    g(10, 10);
    g(10, a);
    g(10, b);
    g(10, c);
}