#include <iostream>
#include <stdexcept>

using namespace std;

void g(int x)
{
    if (x == 1) throw 1;
    if (x == 2) throw 2L;
    if (x == 3) throw 'c';
    if (x == 4) throw (unsigned char) 10;
    if (x == 5) throw std::out_of_range("!"); 
}

void f(int x)
{
    if (x > 0) {
        g(x);
    }
}

/*void handler(void)
{
    exit(42);
}

std::pair<bool, int> add(int x, int y)
{
    int res;
    if(__builtin_add_overflow(x, y, &res)) {
        return { false, res };
    } else {
        return { true, res };
    }
}*/

int main()
{
    int x;
    
    //auto [success, value ] = add(x, y);
    //set_terminate(handler);
    
    cin >> x;
    try {
        f(x);
    } catch (int z) {
        cout << "cought int" << endl;
    } catch(...) {
        abort();
    }
}