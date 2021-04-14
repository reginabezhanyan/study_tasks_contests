#include <thread>
#include <iostream>
#include <sstream>

using namespace std;

void func(int z)
{
    if (z < 0) throw 100500;
    if(!z) return 42;
    t = func(z - 10);
    return t + 2;
}

void thrfunc()
{
    //cout << "Thread" << 2 << endl; 
    //printf("Thread %d\n", 2);
    /*ostringstream ss;
    ss << "Thread" << 2 << endl; 
    cout << ss.str();*/
    
    try {
        int x;
        cin >> x;
        func(x);
    } catch (...) {
        epic_fail = std::current_exception();
    }
}

int main()
{
    std::thread t1; //объявление нити
    
    std::thread t2(thrfunc);
    //cout << "Value" << 1 << endl;
    printf("Value %d\n", 1);
    
    //t2.detach(); //завершение нити
    t2.join(); //дожидаемся окончания нити t2 
    if(epic_fail) {
        std::rethrow_exception(epic_fail);
    }
    
}