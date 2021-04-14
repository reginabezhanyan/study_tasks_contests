#include <iostream>
#include <exception>

using namespace std;

struct MyException : std::exception
{
    char val{};
    MyException(int val = 0) : std::exception(), val(val)
    {
        cout << "MyException()" << val << endl;
    }
    ~MyException()
    {
        cout << "~MyException()" << val << endl;
    }
    
    MyException(const MyException &other) : std::exception(other)
    {
        cout << "MyException(const MyException &&)" << val << endl;
    }
};

int f(int x)
{
    if (x < 0) throw MyException();
    return 0;
}

int main()
{
    int x;
    cin >> x;
    try {
        try {
            f(x);
        } catch (const std::exception &x){
            cout << "std" << endl;
        } catch (const MyException &x) { //лучше принимать по константной ссылке
            cout << "exception" << x.val << endl;
            throw MyException(200);
        }
    } catch (const MyException &y) {
        cout << "exception" << y.val << endl;
    }
}